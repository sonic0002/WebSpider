/********************************************************************************
 * Class       : Parser
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Parser class to parse webpage contents and retrieve links from the
 *				 webpage contents
 ********************************************************************************/
#ifndef PARSER_H
#define PARSER_H
#pragma once
#include <string>
#include <hash_map>
#include "WinRetriever.h"
#include "PendingLink.h"
#include "Phrase.h"
#include "URL.h"

class Parser
{
private:
	WinRetriever wr;
	std::string html;
	hash_map<std::string,std::string> tagHash;

	std::string& stripHTMLTags(std::string& s);
	std::string stripHTMLTagsWithRegEx(std::string s);
	std::string stripSpecifiedHTMLTagsWithRegEx(std::string s,std::string exp);
	std::string getAbsoluteURL(std::string url);
	std::string removeAll(std::string& str,const std::string& needle);
	std::string replaceAll(std::string& str,const std::string& needle,const std::string& replacement);
	bool isInBlackList(const std::string& str);
	int findPhraseNumber(const std::string& str,const std::string& phrase);
public:
	Parser(void);
	Parser(std::string h){setHtml(h);initializeTagHash();}
	Parser(std::string h,WinRetriever w){setHtml(h);setWinRetriever(w);initializeTagHash();}
	~Parser(void);

	//Sets and gets
	void setHtml(std::string h){html=h;}
	std::string getHtml(){return html;}
	void setWinRetriever(WinRetriever w){wr=w;}
	WinRetriever getWinRetriever(){return wr;}

	void initializeTagHash();
	std::string getTitle(const std::string& str);
	std::string getDescription(const std::string& str);
	std::string parseToPlainText();
	vector<PendingLink> getLinks(std::string s);
	hash_map<std::string,int> getKeyWords(std::string str,int weightage=1);
	hash_map<std::string,int> getPhrases(std::string str,const std::vector<Phrase>& phraseList,int weightage=1);
	int calculateLinkLevel(const std::string& url);
	URL parseUrl(const std::string& url);
};
#endif
