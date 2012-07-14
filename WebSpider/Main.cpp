#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "WinRetriever.h"
#include "Parser.h"
//#include "MySQLDatabaseConnection.h"
#include "Logger.h"
#include "LinkManager.h"
#include "DomainManager.h"
#include "LinkKeywordManager.h"
#include "PendingLinkManager.h"
#include "Domain.h"
#include "md5.h"
#include "StringProcessor.h"
#include "HttpResponse.h"
#include "PhraseManager.h"
#include "Configure.h"

using namespace std;
static long totalFiles=0;
static long success=0;
static long fail=0;

void startParsing(const string& content,WinRetriever wr,PendingLink pendingLink,const vector<Phrase>& phraseList,int level){
	//Parse the response 
	Parser parser(content,wr);
	string text=parser.parseToPlainText();
	
	LinkManager linkManager;	
	MD5 md5;
	string md5sum=md5.digestString(const_cast<char*>(text.c_str()));
	bool isContentChanged=false;
	if(!linkManager.isExist(wr.getUrl())||(isContentChanged=linkManager.isContentChanged(wr.getUrl(),md5sum))){	
		Link link;
		link.setUrl(wr.getUrl());
		link.setTitle(parser.getTitle(content));
		link.setMd5sum(md5sum);
		link.setFulltxt(text);
		link.setType("HTML");
		link.setDomainId(pendingLink.getDomainId());
		link.setLevel(parser.calculateLinkLevel(link.getUrl()));

		//Save to link table
		if(isContentChanged){
			linkManager.updateLink(link);
		}else{
			linkManager.addLink(link);
		}
		link=linkManager.getLink(wr.getUrl());
		
		//Start to get phrases in the page	
		hash_map<string,int> phraseMap=parser.getPhrases(text,phraseList);
		hash_map<string,int>::const_iterator phraseStart,phraseEnd;
		phraseEnd=phraseMap.end();
		LinkKeywordManager linkKeywordManager;
		linkKeywordManager.deleteAll(link.getLinkId());			//Delete all link keywords of a link
		for(phraseStart=phraseMap.begin();phraseStart!=phraseEnd;phraseStart++){
			LinkKeyword linkKeyword;
			linkKeyword.setLinkId(link.getLinkId());
			linkKeyword.setKeyword(phraseStart->first);
			linkKeyword.setWeight(phraseStart->second);
			linkKeywordManager.addLinkKeyword(linkKeyword);
		}

		//Get title keywords
		hash_map<string,int> titleKeywordMap=parser.getKeyWords(parser.getTitle(content),3);
		hash_map<string,int>::const_iterator titleKeywordStart,titleKeywordEnd;
		titleKeywordStart=titleKeywordMap.begin();
		titleKeywordEnd=titleKeywordMap.end();

		//Start parse link keywords.
		hash_map<string,int> hm=parser.getKeyWords(text);
		hash_map<string,int>::const_iterator start,end;
		end=hm.end();

		for(start=hm.begin();start!=end;start++){
			for(titleKeywordStart;titleKeywordStart!=titleKeywordEnd;++titleKeywordStart){
				if(hm.find(titleKeywordStart->first)!=hm.end()){
					hm[titleKeywordStart->first]+=titleKeywordStart->second;
				}
			}
		}

		for(start=hm.begin();start!=end;start++){
			LinkKeyword linkKeyword;
			linkKeyword.setLinkId(link.getLinkId());
			linkKeyword.setKeyword(start->first);
			linkKeyword.setWeight(start->second);
			linkKeywordManager.addLinkKeyword(linkKeyword);
		}

		//Add pending links 
		vector<PendingLink> pendingLinks=parser.getLinks(content);
		int size=pendingLinks.size();
		PendingLinkManager pendingLinkManager;
		for(int i=0;i<size;++i){
			PendingLink pendingLink=pendingLinks.at(i);
			pendingLink.setDomainId(link.getDomainId());
			pendingLink.setLevel(parser.calculateLinkLevel(pendingLink.getUrl()));
			if(!pendingLinkManager.isExist(pendingLink.getUrl())&&!linkManager.isExist(pendingLink.getUrl())){
				pendingLinkManager.addPendingLink(pendingLink);
			}
		}
	}
}

bool isInBlackFileList(const string& url){
	static string blackFileList[]={".xml",".mp3"};
	int size=sizeof(blackFileList)/sizeof(string);
	for(int i=0;i<size;++i){
		if(StringProcessor::endWith(StringProcessor::tolower(StringProcessor::trim(url)),blackFileList[i])){
			return true;
		}
	}
	return false;
}

HttpResponse buildHttpResponse(string& str){
	HttpResponse response;
	string::size_type pos(0);
	
	if((pos=str.find("HTTP/1.1"))!=string::npos){
		response.setResponseCode(str.substr(pos+9,3));
	}else{
		response.setResponseCode("000");
	}

	//Get the response header
	if((pos=str.find("\r\n\r\n"))!=string::npos){
		string responseHeader=StringProcessor::toupper(str.substr(0,pos));
		string::size_type headerStartPos(0);
		if((headerStartPos=responseHeader.find("CONTENT-TYPE"))!=string::npos){
			//Get the content type
			headerStartPos=responseHeader.find_first_of(":",headerStartPos)+1;
			string contentType=StringProcessor::trim(responseHeader.substr(headerStartPos,responseHeader.find_first_of("\r",headerStartPos)-headerStartPos));
			response.setContentType(contentType);
		}
		response.setResponseHeader(str.substr(0,pos));
	}

	if(str.find_first_of("<")!=string::npos){
		if(str.find_last_of(">")!=string::npos){
			str=str.substr(str.find_first_of("<"),str.find_last_of(">")-str.find_first_of("<")+1);
		}else{
			str=str.substr(str.find_first_of("<"));
		}
		response.setSourceCode(str);
		response.setSourceCodeLength(str.length());
	}
	return response;
}

void startIndexing(PendingLink pendingLink,const vector<Phrase>& phraseList,bool canLeaveDomain,int level){
	Logger::log("Start indexing "+pendingLink.getUrl());
	++totalFiles;
	LinkManager linkManager;
	DomainManager domainManager;
	if(!isInBlackFileList(pendingLink.getUrl())){	
		//Create retriever object to retrieve page content
		WinRetriever wr(pendingLink.getUrl());
		wr.initialize();
		if((canLeaveDomain||(!canLeaveDomain&&wr.getHost()==Configure::hostname)&&(!level||pendingLink.getLevel()<=level))){
			wr.connect();
			string response=wr.retrieve();
			wr.close();

			HttpResponse responseObj=buildHttpResponse(response);
			if(responseObj.getReponseCode()=="200"||responseObj.getReponseCode()=="302"){
				if(responseObj.getContentType()!="TEXT/HTML"){
					cout<<"Content Type : "<<responseObj.getContentType()<<endl;
				}
				string protocol=wr.getProtocol();
				if(StringProcessor::trim(protocol).empty()){
					protocol+="http";
				}
				string domainStr=protocol+"://"+wr.getHost();
				int domainId=0;
				if(!domainManager.isExist(domainStr)){
					Domain domain;
					domain.setUrl(domainStr);
					domain.setStatus("allowed");
					domainManager.addDomain(domain);
				}
				domainId=domainManager.getDomain(domainStr).getDomainId();
				pendingLink.setDomainId(domainId);
				//Start parsing the page content
				startParsing(responseObj.getSourceCode(),wr,pendingLink,phraseList,level);
				++success;
			}else{
				cout<<"HTTP response : "<<responseObj.getReponseCode()<<endl;
				++fail;
			}
		}else{
			wr.close();
			++fail;
		}
	}else{
		++fail;
	}

	Logger::log("Finish indexing "+pendingLink.getUrl());
}

void showHelp(){
	cout<<"Usage : webspider [-d domain] [-c] [-h] [-l level] [-r]"<<endl;
	cout<<"\t -d : Domain name to start index"<<endl;
	cout<<"\t -c : Can leave the doman or nor. If present, then can leave domain"<<endl;
	cout<<"\t -l : Index level"<<endl;
	cout<<"\t -r : Reindex all"<<endl;
	cout<<"\t -h : Help information"<<endl;
}

int main(int argc,char** argv){
	_CrtDumpMemoryLeaks();
	DWORD tstart,tend,tdiff;
	tstart = GetTickCount();
	if(argc<3){
		showHelp();
		exit(-1);
	}

	//Start processing command line arguments
	int index=1;
	while(index<argc){
		if(argv[index][0]=='-'){
			switch(argv[index][1]){
			case 'd' : if(argv[++index]!=NULL&&argv[index][0]!='-'){
						  Configure::hostname=string(argv[index]);
					   }else{
						  showHelp();
						  exit(-1);
					   };break;
			case 'c' : Configure::canLeaveDomain=true; break;
			case 'l' : if(argv[++index]!=NULL&&argv[index][0]!='-'){
						  Configure::level=StringProcessor::parseInt(string(argv[index]));
					   }else{
						  showHelp();
						  exit(-1);
					   }
			case 'r' : Configure::reindex=true;break;
			case 'h' : showHelp();break;
			}
		}
		++index;
	}

	//Create database connection to retrieve domains to be indexed
	DomainManager* domainManager=new DomainManager;
	Domain domain;
	domain.setUrl(Configure::hostname);
	domain.setStatus("allowed");
	if(!domainManager->isExist(domain.getUrl())){
		domainManager->addDomain(domain);
	}
	domain=domainManager->getDomain(domain.getUrl());
	delete domainManager;

	//Get all the phrase list from database
	PhraseManager phraseManager;
	vector<Phrase> phraseList=phraseManager.getAllPhrases();
	
	//Check whether reindex or not
	if(Configure::reindex){
		LinkManager linkManager;
		linkManager.deleteAll();
		
		PendingLinkManager pendingLinkManager;
		pendingLinkManager.deleteAll();

		LinkKeywordManager linkKeyWordManager;
		linkKeyWordManager.deleteAll();
	}
	
	//Start indexing
	PendingLink startLink;
	startLink.setUrl(domain.getUrl());
	startLink.setDomainId(domain.getDomainId());
	startIndexing(startLink,phraseList,Configure::canLeaveDomain,Configure::level);
	
	PendingLinkManager pendingLinkManager;
	while(true){
		vector<PendingLink> pendingLinks=pendingLinkManager.getAllPendingLink();
		int size=pendingLinks.size();
		if(size==0){
			break;
		}

		for(int i=0;i<size;++i){
			PendingLink pendingLink=pendingLinks.at(i);
			startIndexing(pendingLink,phraseList,Configure::canLeaveDomain,Configure::level);
			pendingLinkManager.deletePendingLink(pendingLink.getUrl());
		}
	}

	tend=GetTickCount();

	Logger::log("Finish indexing");
	Logger::log("Time spendt : "+StringProcessor::intToString((tend-tstart)/6000));
	cout<<"Total fles :"<<totalFiles<<endl;
	cout<<"Success : "<<success<<endl;
	cout<<"Fail : "<<fail<<endl;

	return 0;
}