#include "WinRetriever.h"
#include "Parser.h"
#include "MySQLDatabaseConnection.h"
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

using namespace std;

void startParsing(const string& content,WinRetriever wr,Domain domain,const vector<Phrase>& phraseList){
	//Parse the response 
	Parser parser(content,wr);
	string text=parser.parseToPlainText();
	
	LinkManager linkManager;
	MD5 md5;
	if(!linkManager.isExist(wr.getUrl())){
		Link link;
		link.setUrl(wr.getUrl());
		link.setTitle(parser.getTitle(content));
		link.setFulltxt(text);
		link.setMd5sum(md5.digestString(const_cast<char*>(text.c_str())));
		link.setType("HTML");
		link.setDomainId(domain.getDomainId());
		
		//Save to link table
		linkManager.addLink(link);
		link=linkManager.getLink(wr.getUrl());

		//Start to get phrases in the page
		hash_map<string,int> phraseMap=parser.getPhrases(text,phraseList);
		hash_map<string,int>::const_iterator phraseStart,phraseEnd;
		phraseEnd=phraseMap.end();
		LinkKeywordManager linkKeywordManager;
		for(phraseStart=phraseMap.begin();phraseStart!=phraseEnd;phraseStart++){
			LinkKeyword linkKeyword;
			linkKeyword.setLinkId(link.getLinkId());
			linkKeyword.setKeyword(phraseStart->first);
			linkKeyword.setWeight(phraseStart->second);
			linkKeywordManager.addLinkKeyword(linkKeyword);
		}

		//Start parse link keywords.
		hash_map<string,int> hm=parser.getKeyWords(text);
		hash_map<string,int>::const_iterator start,end;
	
		end=hm.end();
		for(start=hm.begin();start!=end;start++){
			LinkKeyword linkKeyword;
			linkKeyword.setLinkId(link.getLinkId());
			linkKeyword.setKeyword(start->first);
			linkKeyword.setWeight(start->second);
			linkKeywordManager.addLinkKeyword(linkKeyword);
		}
		vector<PendingLink> pendingLinks=parser.getLinks(content);
		int size=pendingLinks.size();
		PendingLinkManager pendingLinkManager;
		for(int i=0;i<size;++i){
			PendingLink pendingLink=pendingLinks.at(i);
			pendingLink.setDomainId(domain.getDomainId());
			if(!pendingLinkManager.isExist(pendingLink.getUrl())&&!linkManager.isExist(pendingLink.getUrl())){
				pendingLinkManager.addPendingLink(pendingLink);
			}
		}
	}
}

void startParsing(const string& content,WinRetriever wr,PendingLink pendingLink,const vector<Phrase>& phraseList){
	//Parse the response 
	Parser parser(content,wr);
	string text=parser.parseToPlainText();
	
	LinkManager linkManager;	
	MD5 md5;
	if(!linkManager.isExist(wr.getUrl())){
		Link link;
		link.setUrl(wr.getUrl());
		link.setTitle(parser.getTitle(content));
		link.setMd5sum(md5.digestString(const_cast<char*>(text.c_str())));
		link.setFulltxt(text);
		link.setType("HTML");
		link.setDomainId(pendingLink.getDomainId());
		
		//Save to link table
		linkManager.addLink(link);
		link=linkManager.getLink(wr.getUrl());

		//Start to get phrases in the page
		hash_map<string,int> phraseMap=parser.getPhrases(text,phraseList);
		hash_map<string,int>::const_iterator phraseStart,phraseEnd;
		phraseEnd=phraseMap.end();
		LinkKeywordManager linkKeywordManager;
		for(phraseStart=phraseMap.begin();phraseStart!=phraseEnd;phraseStart++){
			LinkKeyword linkKeyword;
			linkKeyword.setLinkId(link.getLinkId());
			linkKeyword.setKeyword(phraseStart->first);
			linkKeyword.setWeight(phraseStart->second);
			linkKeywordManager.addLinkKeyword(linkKeyword);
		}

		//Start parse link keywords.
		hash_map<string,int> hm=parser.getKeyWords(text);
		hash_map<string,int>::const_iterator start,end;
	
		end=hm.end();
		
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

void startIndexing(Domain domain,const vector<Phrase>& phraseList,bool canLeaveDomain=true){
	Logger::log("Start indexing "+domain.getUrl());
	LinkManager linkManager;
	DomainManager domainManager;
	if(!isInBlackFileList(domain.getUrl())){
		if(!linkManager.isExist(domain.getUrl())){
			//Create retriever object to retrieve page content
			WinRetriever wr(domain.getUrl());
			wr.initialize();
			if(wr.getHost()=="localhost"){
				wr.connect();
				string response=wr.retrieve();
				wr.close();

				HttpResponse responseObj=buildHttpResponse(response);
				if(responseObj.getReponseCode()=="200"){
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
					domain.setDomainId(domainId);
					startParsing(responseObj.getSourceCode(),wr,domain,phraseList);
				}else{
					cout<<"HTTP response : "<<responseObj.getReponseCode()<<endl;
				}
			}else{
				wr.close();
			}
		}
	}
	Logger::log("Finish indexing "+domain.getUrl());
}

void startIndexing(PendingLink pendingLink,const vector<Phrase>& phraseList,bool canLeaveDomain=true){
	Logger::log("Start indexing "+pendingLink.getUrl());
	
	LinkManager linkManager;
	DomainManager domainManager;
	if(!isInBlackFileList(pendingLink.getUrl())){
		if(!linkManager.isExist(pendingLink.getUrl())){
			//Create retriever object to retrieve page content
			WinRetriever wr(pendingLink.getUrl());
			wr.initialize();
			if(wr.getHost()=="localhost"){
				wr.connect();
				string response=wr.retrieve();
				wr.close();

				HttpResponse responseObj=buildHttpResponse(response);
				if(responseObj.getReponseCode()=="200"){
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
					startParsing(responseObj.getSourceCode(),wr,pendingLink,phraseList);
				}else{
					cout<<"HTTP response : "<<responseObj.getReponseCode()<<endl;
				}
			}else{
				wr.close();
			}
		}
	}
	Logger::log("Finish indexing "+pendingLink.getUrl());
}

int main(){
	//Create database connection to retrieve domains to be indexed
	DomainManager* domainManager=new DomainManager;
	Domain domain;
	domain.setUrl("http://localhost");
	domain.setStatus("allowed");
	if(!domainManager->isExist(domain.getUrl())){
		domainManager->addDomain(domain);
	}

	PhraseManager phraseManager;
	vector<Phrase> phraseList=phraseManager.getAllPhrases();

	startIndexing(domain,phraseList,false);
	/*
	vector<Domain> domainList=domainManager->getAllowedDomains();
	int size=domainList.size();
	for(int i=0;i<size;++i){
		startIndexing(domainList.at(i));
	}
	*/
	PendingLinkManager pendingLinkManager;
	while(true){
		vector<PendingLink> pendingLinks=pendingLinkManager.getAllPendingLink();
		int size=pendingLinks.size();
		if(size==0){
			break;
		}
		for(int i=0;i<size;++i){
			PendingLink pendingLink=pendingLinks.at(i);
			startIndexing(pendingLink,phraseList,false);
			pendingLinkManager.deletePendingLink(pendingLink.getUrl());
		}
	}
	Logger::log("Finish indexing");
	return 0;
}