/********************************************************************************
 * Class       : PendingLinkManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle pending link data, search, update, insert or delete
 ********************************************************************************/
#pragma once
#include <vector>
#include "databasemanager.h"
#include "PendingLink.h"

class PendingLinkManager :
	public DatabaseManager
{
public:
	PendingLinkManager(void);
	~PendingLinkManager(void);

	void addPendingLink(PendingLink& pendingLink);
	bool isExist(const string& url);
	//PendingLink getPendingLink(const string& url);
	vector<PendingLink> getAllPendingLink();
	void deletePendingLink(const string& url);
};

