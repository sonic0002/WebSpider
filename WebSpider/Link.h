/********************************************************************************
 * Class       : Link
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Link entity
 ********************************************************************************/
#ifndef LINK_H
#define LINK_H
#pragma once
#include <string>

class Link
{
public:
	Link(void):type("HTML"){};
	~Link(void);

	//Sets and gets
	void setLinkId(const int linkId){this->linkId=linkId;}
	int getLinkId(){return this->linkId;}
	void setUrl(const std::string& url){this->url=url;}
	std::string getUrl(){return this->url;}
	void setTitle(const std::string& title){this->title=title;}
	std::string getTitle(){return this->title;}
	void setFulltxt(const std::string& fulltxt){this->fulltxt=fulltxt;}
	std::string getFulltxt(){return this->fulltxt;}
	void setType(const std::string& type){this->type=type;}
	std::string getType(){return this->type;}
	void setMd5sum(const std::string& md5sum){this->md5sum=md5sum;}
	std::string getMd5sum(){return this->md5sum;}
	void setDomainId(const int domainId){this->domainId=domainId;}
	int getDomainId(){return this->domainId;}
	void setLevel(const int level){this->level=level;}
	int getLevel(){return this->level;}
private:
	std::string url;
	std::string title;
	int linkId;
	std::string fulltxt;
	std::string md5sum;
	std::string type;
	int domainId;
	int level;
};
#endif
