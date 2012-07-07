/********************************************************************************
 * Class       : LinkKeywordManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle link keyword data, search, update, insert or delete
 ********************************************************************************/
#pragma once
#include "databasemanager.h"
#include "LinkKeyword.h"

class LinkKeywordManager :
	public DatabaseManager
{
public:
	LinkKeywordManager(void);
	~LinkKeywordManager(void);

	void addLinkKeyword(LinkKeyword& linkKeyword);
	LinkKeyword getLinkKeyword(int linkId,const string& keyword);
	bool isExist(int linkId,const string& keyWord);
};

