/********************************************************************************
 * Class       : LinkManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle link data, search, update, insert or delete
 ********************************************************************************/
#pragma once
#include "databasemanager.h"
#include "Link.h"

class LinkManager :
	public DatabaseManager
{
public:
	LinkManager(void);
	~LinkManager(void);

	void addLink(Link& link);
	Link getLink(const int linkId);
	Link getLink(const string& url);
	bool isExist(const string& url);
};

