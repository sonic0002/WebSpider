/********************************************************************************
 * Class       : LinkManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle link data, search, update, insert or delete
 ********************************************************************************/
#ifndef LINK_MANAGER_H
#define LINK_MANAGER_H
#pragma once
#include <string>
#include "databasemanager.h"
#include "Link.h"

class LinkManager :
	public DatabaseManager
{
public:
	LinkManager(void);
	~LinkManager(void);

	void addLink(Link& link);
	int updateLink(Link& link);
	Link getLink(const int linkId);
	Link getLink(const std::string& url);
	bool isExist(const std::string& url);
	long deleteAll();
	bool isContentChanged(const std::string& url,const std::string& checksum);
};
#endif
