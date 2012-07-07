/********************************************************************************
 * Class       : DomainManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle domain data, search, update, insert or delete
 ********************************************************************************/
#pragma once
#include "databasemanager.h"
#include "Domain.h"

class DomainManager :
	public DatabaseManager
{
public:
	DomainManager(void);
	//DatabaseManager(const string& hostname,const string& username,const string& password,const string& database);
	vector<Domain> getAllDomains();
	vector<Domain> getAllowedDomains();
	vector<Domain> getBlockedDomains();
	Domain getDomain(const string& url);
	int getDomainId(const string& url);
	void addDomain(Domain& domain);
	bool isExist(const string& url);

	~DomainManager(void);
};

