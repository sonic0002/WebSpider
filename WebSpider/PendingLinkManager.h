/********************************************************************************
 * Class       : PendingLinkManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle pending link data, search, update, insert or delete
 ********************************************************************************/
#ifndef PENDING_LINK_MANAGER_H
#define PENDING_LINK_MANAGER_H
#pragma once
#include <vector>
#include <string>
#include "databasemanager.h"
#include "PendingLink.h"

class PendingLinkManager :
	public DatabaseManager
{
public:
	PendingLinkManager(void);
	~PendingLinkManager(void);

	void addPendingLink(PendingLink& pendingLink);
	bool isExist(const std::string& url);
	//PendingLink getPendingLink(const string& url);
	std::vector<PendingLink> getAllPendingLink();
	void deletePendingLink(const std::string& url);
	long deleteAll();
};
#endif
