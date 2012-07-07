#include <iostream>
#include <regex>
#include <sstream>
#include "StringProcessor.h"
#include "Parser.h"

Parser::Parser(void){
	initializeTagHash();
}

/************************************************************************
 * Method     : initializeTagHash()
 * Descrition : initialize the speficied tag hash. Some tags in html
				documents are not considered as content tag. They are 
				functional tags. There tags include <script> and <style>,
				they should be treated differently from other tags such as
				<a> and <img>
 * Input      : void
 * Output     : void
*************************************************************************/
void Parser::initializeTagHash(){
	tagHash["script"]="<script([^>]*)>[^]*?</script>";						//Match JavaScript tag and its contents,[^]* is a tricky part,it can match multiline contents
	tagHash["style"] ="<style(.*)>.*?</style>";								//Match Cascade Style Sheet tag and its contents,[^]* is a tricky part,it can match multiline contents
}

/************************************************************************
 * Method     : stripHTMLTags()
 * Descrition : Remove <> tags from the HTML source code.
 * Input      : s -- Page content to be processed
 * Output     : The processed page content
*************************************************************************/
string& Parser::stripHTMLTags(string& s) {
	static bool inTag = false;
	bool done = false;
	size_t leftPos;
	while(!done) {
		if(inTag) {
			// The previous line started an HTML tag
			// but didn't finish. Must search for '>'.
			size_t rightPos = s.find('>');
			if(rightPos != string::npos) {
				inTag = false;
				s.erase(leftPos, rightPos + 1);
			}
			else {
				done = true;
				s.erase();
			}
		}
		else {
			// Look for start of tag:
			leftPos = s.find('<');
			if(leftPos != string::npos) {
				// See if tag close is in this line:
				size_t rightPos = s.find('>');
				if(rightPos == string::npos) {
					inTag = done = true;
					s.erase(leftPos);
				}
				else
					s.erase(leftPos, rightPos - leftPos + 1);
			}
			else
				done = true;
		}
	}

	// Etc...
	return s;
}

/************************************************************************
 * Method     : stripSpecifiedHTMLTagsWithRegEx()
 * Descrition : this function is to strip away some specified tags in an 
 *              html file, such as <script> and <style>. The contents in 
 *              JavaScript tag and CSS tag should be stripped away
 * Input      : s--string to be processed
 *              exp--regular expression to be used         
 * Output     : string after striping the specified tag
*************************************************************************/
string Parser::stripSpecifiedHTMLTagsWithRegEx(string s,string exp){
	using namespace std::tr1;
	regex rg(exp,std::tr1::regex_constants::icase);
	string replacement(" ");
	return regex_replace(s,rg,replacement);
}

/************************************************************************
 * Method     : stripHTMLTagsWithRegEx()
 * Descrition : this function is to strip away some general html tags such 
                as <link>, <img> and <a>. These tags can be stripped away 
				easily
 * Input      : s--string to be processed    
 * Output     : string after striping the HTML tag
*************************************************************************/
string Parser::stripHTMLTagsWithRegEx(string s){
	using namespace std::tr1;
	regex rg("<.*?>");
	string replacement(" ");

	string str=replaceAll(s,"\r\n",replacement);
	str=replaceAll(str,"\n",replacement);
	str=replaceAll(str,"\r",replacement);														//Remove all the line feeds
	str=stripSpecifiedHTMLTagsWithRegEx(s,tagHash["script"]);						            //Call the replacement function
	str=stripSpecifiedHTMLTagsWithRegEx(str,tagHash["style"]);
	str=regex_replace(str,rg,replacement);
	return str;
}

/************************************************************************
 * Method     : removeAll()
 * Descrition : remove all the needles found in the str
 * Input      : str -- string to be processed
 *	            needle -- the string to be replaced
 * Output     : string after striping the HTML tag
*************************************************************************/
string Parser::removeAll(string& str,const string& needle){
	string::size_type pos = 0;									// Must initialize
    while (( pos = str.find (needle,pos) ) != string::npos){
        str.erase(pos,needle.length());
    }
	return str;
}

/************************************************************************
 * Method     : replaceAll()
 * Descrition : replace all the matched patterns found in the str
 * Input      : str -- string to be processed
 *	            expr -- regular expression
 *              replacement -- the string to replace the needle
 * Output     : string after replacement
*************************************************************************/
string Parser::replaceAll(string& str,const string& pattern,const string& replacement){
	using namespace std::tr1;
	regex rg(pattern);
	str=regex_replace(str,rg,replacement);
	return str;
}

/************************************************************************
 * Method     : getTitle()
 * Descrition : get the title of the page
 * Input      : page source code       
 * Output     : title of the page
*************************************************************************/
string Parser::getTitle(const string& str){
	using namespace std::tr1;
	string title("");
	string::const_iterator start,end;
	start=str.begin();
	end=str.end();
	match_results<std::string::const_iterator> what;
	std::tr1::regex_constants::match_flag_type flags = std::tr1::regex_constants::match_default;
	regex rg("<title>(.*?)</title>",std::tr1::regex_constants::icase);

	while(regex_search(start,end,what,rg,flags)){			//This function is very important to match all <title></title>
		for(size_t i=1; i < what.size(); i++){
			if(what[i]!=""){
				title=StringProcessor::trim(what[i]);
			}
		}
		start = what[0].second;
		flags |= std::tr1::regex_constants::match_prev_avail;
	}
	return title;
}

/************************************************************************
 * Method     : getDescription()
 * Descrition : get the meta description of the page
 * Input      : page source code       
 * Output     : meta description of the page
*************************************************************************/
string Parser::getDescription(const string& str){
	using namespace std::tr1;
	string description("");
	string::const_iterator start,end;
	start=str.begin();
	end=str.end();
	match_results<std::string::const_iterator> what;
	std::tr1::regex_constants::match_flag_type flags = std::tr1::regex_constants::match_default;
	string pattern="<meta.*?name=\\\"description\\\".*?content=\\\"(.*?)\\\".*?>|<meta.*?content=\\\"(.*?)\\\".*?name=\\\"description\\\".*?>";
	regex rg(pattern,std::tr1::regex_constants::icase);

	while(regex_search(start,end,what,rg,flags)){			//This function is very important to match all <title></title>
		for(size_t i=1; i < what.size(); i++){
			if(what[i]!=""){
				description=StringProcessor::trim(what[i]);
			}
		}
		start = what[0].second;
		flags |= std::tr1::regex_constants::match_prev_avail;
	}
	return description;
}

/************************************************************************
 * Method     : parseToPlainText()
 * Descrition : this function is to process the HTML and return a string
				without HTML tags in side
 * Input      : void        
 * Output     : string after processing
*************************************************************************/
string Parser::parseToPlainText(){
	using namespace std::tr1;
	regex rg("\r|\n|( +)|(&nbsp;)|,");
	string replacement(" ");
	string plainText=stripHTMLTagsWithRegEx(html);
	plainText=regex_replace(plainText,rg,replacement);
	return plainText;
}

/************************************************************************
 * Method     : getLinks()
 * Descrition : get all the elements with tag <a> and retrieve all the
				hrefs from the <a> elements
 * Input      : void        
 * Output     : A list of pending links
*************************************************************************/
vector<PendingLink> Parser::getLinks(string s){
	using namespace std::tr1;
	vector<PendingLink> result_links;
	string::const_iterator start,end;
	start=s.begin();
	end=s.end();
	match_results<std::string::const_iterator> what;
	std::tr1::regex_constants::match_flag_type flags = std::tr1::regex_constants::match_default;
	regex rg("<a.*?href=(.*?) .*?>",std::tr1::regex_constants::icase);

	while(regex_search(start,end,what,rg,flags)){			//This function is very important to match all <a href="">
		for(size_t i=1; i < what.size(); i++){
			if(what[i]!=""){
				PendingLink link;
				string href=StringProcessor::trim(what[i]);
				string::size_type quote_pos=href.find_first_of('"');
				if(quote_pos!=string::npos){
					string::size_type last_quote_pos=href.find('"',quote_pos+1);
					if(last_quote_pos!=string::npos){
						href=href.substr(quote_pos+1,last_quote_pos-quote_pos-1);
					}else{
						href=href.substr(quote_pos+1);
					}
				}else if((quote_pos=href.find_first_of('\''))!=string::npos){
					string::size_type last_quote_pos=href.find('\'',quote_pos+1);
					if(last_quote_pos!=string::npos){
						href=href.substr(quote_pos+1,last_quote_pos-quote_pos-1);
					}else{
						href=href.substr(quote_pos+1);
					}
				}
				
				href=StringProcessor::trim(href);
				if(!StringProcessor::beginWith(StringProcessor::tolower(href),"javascript:")&&!StringProcessor::beginWith(StringProcessor::tolower(href),"mailto:")){
					href=getAbsoluteURL(href);
					cout<<href<<endl;
					link.setUrl(href);
					result_links.push_back(link);
				}
			}
		}
		start = what[0].second;
		flags |= std::tr1::regex_constants::match_prev_avail;
	}

	return result_links;
}

/************************************************************************
 * Method     : getAbsoluteURL()
 * Descrition : return the absolute url for any url no matter is is a 
				relative path or an absolute path
 * Input      : url -- URL to be built    
 * Output     : formmated url
*************************************************************************/
string Parser::getAbsoluteURL(string url){
	if(url.find("://")!=string::npos){
		return url;
	}	//If it is a absolute URL now, return immediately

	if(url.find(wr.getHost())!=string::npos){
		return url;
	}else{
		//Process the protocol
		string protocol=wr.getProtocol();
		if(StringProcessor::trim(protocol).empty()){
			protocol="http";
		}

		//Process the hostname
		string hostname=wr.getHost();
		if(StringProcessor::endWith(StringProcessor::trim(hostname),"/")){
			hostname=hostname.erase(hostname.length()-1,1);
		}

		//Process the path
		url=StringProcessor::trim(url);
		string base=wr.getBase();
		int backCount=StringProcessor::substrCount(url,"../");              //Get number of ocuurences of ../ in url
		int baseBackCount=StringProcessor::substrCount(base,"/");           //Get number of occurences of / in base of the URL
		if(baseBackCount<backCount){
			string::size_type pos(0);
			while(pos!=string::npos){
				pos=url.find("../");
				if(pos!=string::npos){
					url=url.erase(pos,3);
				}
			}
		}else if(backCount!=0){
			string::size_type pos(0);
			string::size_type basePos(0);
			while(pos!=string::npos){
				pos=url.find("../");
				if(pos!=string::npos){
					url=url.erase(pos,3);
				}
				basePos=base.find_last_of("/");
				if(basePos!=string::npos){
					base=base.erase(basePos,base.length()-basePos);
				}
			}
			url=base+url;
		}else if(url.find("./")!=string::npos){
			url=url.substr(url.find("./"+2));
		}
			
		if(!StringProcessor::beginWith(url,"/")){
			url="/"+url;
		}

		return (protocol+"://"+hostname+url);
	}
	return string("");
}

/************************************************************************
 * Method     : getAbsoluteURL()
 * Descrition : return the absolute url for any url no matter is is a 
                relative path or an absolute path
 * Input      : str -- Page content  
 8				weightage -- The weitage of a word
 * Output     : keyword pair (UPPER CASE format
*************************************************************************/
hash_map<string,int> Parser::getKeyWords(string str,int weightage){
	//Stopwords : ,;"
	char *delim=" ,;\"";    
	char *tok=strtok((char*)(str.c_str()),delim);
	hash_map<string,int> keywords;
	while(tok!=NULL){
		string s_tok(tok);
		s_tok=StringProcessor::toupper(StringProcessor::trim(s_tok));
		if(s_tok!=""&&!this->isInBlackList(s_tok)){
			if(keywords.find(s_tok)!=keywords.end()){
				keywords[s_tok]+=weightage;
			}else{
				keywords[s_tok]=weightage;
			}
		}
		tok=strtok(NULL,delim);
	}
	return keywords;
}

/************************************************************************
 * Method     : isInBlackList()
 * Descrition : Check whether a string is in black list so that it should
 *              not be indexed
 * Input      : str -- String to be checked  
 * Output     : true or false
*************************************************************************/
bool Parser::isInBlackList(const string& str){
	//Build the black list array
	const static string blackList[]={"A","THE"};
	int size=sizeof(blackList)/sizeof(string);

	for(int i=0;i<size;++i){
		if(str.compare(blackList[i])==0){
			return true;
		}
	}
	return false;
}

Parser::~Parser(void){
}
