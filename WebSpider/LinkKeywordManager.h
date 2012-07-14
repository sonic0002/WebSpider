/********************************************************************************
 * Class       : LinkKeywordManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle link keyword data, search, update, insert or delete
 ********************************************************************************/
#ifndef LINK_KEYWORD_MANAGER_H
#define LINK_KEYWORD_MANAGER_H
#pragma once
#include <string>
#include "databasemanager.h"
#include "LinkKeyword.h"

class LinkKeywordManager :
	public DatabaseManager
{
public:
	LinkKeywordManager(void);
	~LinkKeywordManager(void);

	void addLinkKeyword(LinkKeyword& linkKeyword);
	int updateLinkKeyword(LinkKeyword& linkKeyword);
	LinkKeyword getLinkKeyword(int linkId,const std::string& keyword);
	bool isExist(int linkId,const std::string& keyWord);
	long deleteAll();
	long deleteAll(int linkId);
};
#endif
