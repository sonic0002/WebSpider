/********************************************************************************
 * Class       : DatabaseManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle database data, search, update, insert or delete
 ********************************************************************************/
#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#pragma once
#include <vector>
#include <string>

class DatabaseManager
{
public:
	DatabaseManager(void);
	void setHostname(const std::string& hostname){this->hostname=hostname;}
	std::string getHostname(){return this->hostname;}
	void setUsername(const std::string& username){this->username=username;}
	std::string getUsername(){return this->username;}
	void setPassword(const std::string& password){this->password=password;}
	std::string getPassword(){return this->password;}
	void setDatabase(const std::string& database){this->database=database;}
	std::string getDatabase(){return this->database;}
	virtual ~DatabaseManager(void);
protected:
	std::string hostname;
	std::string username;
	std::string password;
	std::string database;
};
#endif
