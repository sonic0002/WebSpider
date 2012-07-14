/********************************************************************************
 * Class       : PendingLink
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Pending link entity
 ********************************************************************************/
#ifndef PENDING_LINK_H
#define PENDING_LINK_H
#pragma once
#include <string>

class PendingLink
{
public:
	PendingLink(void);
	~PendingLink(void);

	void setLinkId(const int linkId){this->linkId=linkId;}
	int getLinkId(){return this->linkId;}
	void setUrl(const std::string& url){this->url=url;}
	std::string getUrl(){return this->url;}
	void setDomainId(const int domainId){this->domainId=domainId;}
	int getDomainId(){return this->domainId;}
	void setLevel(const int level){this->level=level;}
	int getLevel(){return this->level;}
private:
	int linkId;
	std::string url;
	int domainId;
	int level;
};
#endif
