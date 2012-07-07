/********************************************************************************
 * Class       : Domain
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Domain entity
 ********************************************************************************/
#pragma once
#include <string>

class Domain
{
public:
	Domain(void);
	~Domain(void);
	
	void setDomainId(const int domainId){this->domainId=domainId;}
	int getDomainId(){return this->domainId;}
	void setUrl(const std::string url){this->url=url;}
	std::string getUrl(){return this->url;}
	void setStatus(const std::string status){this->status=status;}
	std::string getStatus(){return this->status;}
private:
	int domainId;
	std::string url;
	std::string status;
};

