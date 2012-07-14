/********************************************************************************
 * Class       : DomainManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle domain data, search, update, insert or delete
 ********************************************************************************/
#ifndef DOMAIN_MANAGER_H
#define DOMAIN_MANAGER_H
#pragma once
#include <vector>
#include <string>
#include "databasemanager.h"
#include "Domain.h"

class DomainManager :
	public DatabaseManager
{
public:
	DomainManager(void);
	//DatabaseManager(const string& hostname,const string& username,const string& password,const string& database);
	std::vector<Domain> getAllDomains();
	std::vector<Domain> getAllowedDomains();
	std::vector<Domain> getBlockedDomains();
	Domain getDomain(const std::string& url);
	int getDomainId(const std::string& url);
	void addDomain(Domain& domain);
	bool isExist(const std::string& url);

	~DomainManager(void);
};
#endif
