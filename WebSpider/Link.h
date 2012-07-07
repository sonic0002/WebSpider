/********************************************************************************
 * Class       : Link
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Link entity
 ********************************************************************************/
#pragma once
#include <string>
using namespace std;

class Link
{
public:
	Link(void):type("HTML"){};
	~Link(void);

	//Sets and gets
	void setLinkId(const int linkId){this->linkId=linkId;}
	int getLinkId(){return this->linkId;}
	void setUrl(const string& url){this->url=url;}
	string getUrl(){return this->url;}
	void setTitle(const string& title){this->title=title;}
	string getTitle(){return this->title;}
	void setFulltxt(const string& fulltxt){this->fulltxt=fulltxt;}
	string getFulltxt(){return this->fulltxt;}
	void setType(const string& type){this->type=type;}
	string getType(){return this->type;}
	void setMd5sum(const string& md5sum){this->md5sum=md5sum;}
	string getMd5sum(){return this->md5sum;}
	void setDomainId(const int domainId){this->domainId=domainId;}
	int getDomainId(){return this->domainId;}
private:
	string url;
	string title;
	int linkId;
	string fulltxt;
	string md5sum;
	string type;
	int domainId;
};

