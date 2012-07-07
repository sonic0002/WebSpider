/********************************************************************************
 * Class       : Parser
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Parser class to parse webpage contents and retrieve links from the
 *				 webpage contents
 ********************************************************************************/
#pragma once
#include <string>
#include <hash_map>
#include "WinRetriever.h"
#include "PendingLink.h"
#include "Phrase.h"

using namespace std;
using namespace stdext;

class Parser
{
private:
	WinRetriever wr;
	string html;
	hash_map<string,string> tagHash;

	string& stripHTMLTags(string& s);
	string stripHTMLTagsWithRegEx(string s);
	string stripSpecifiedHTMLTagsWithRegEx(string s,string exp);
	string getAbsoluteURL(string url);
	string removeAll(string& str,const string& needle);
	string replaceAll(string& str,const string& needle,const string& replacement);
	bool isInBlackList(const string& str);
	int findPhraseNumber(const string& str,const string& phrase);
public:
	Parser(void);
	Parser(string h){setHtml(h);initializeTagHash();}
	Parser(string h,WinRetriever w){setHtml(h);setWinRetriever(w);initializeTagHash();}
	~Parser(void);

	//Sets and gets
	void setHtml(string h){html=h;}
	string getHtml(){return html;}
	void setWinRetriever(WinRetriever w){wr=w;}
	WinRetriever getWinRetriever(){return wr;}

	void initializeTagHash();
	string getTitle(const string& str);
	string getDescription(const string& str);
	string parseToPlainText();
	vector<PendingLink> getLinks(string s);
	hash_map<string,int> getKeyWords(string str,int weightage=1);
	hash_map<string,int> getPhrases(string str,const vector<Phrase>& phraseList,int weightage=1);
};

