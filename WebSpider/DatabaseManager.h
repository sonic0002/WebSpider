/********************************************************************************
 * Class       : DatabaseManager
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Handle database data, search, update, insert or delete
 ********************************************************************************/
#pragma once
#include <vector>
#include <string>
using namespace std;

class DatabaseManager
{
public:
	DatabaseManager(void);
	void setHostname(const string& hostname){this->hostname=hostname;}
	string getHostname(){return this->hostname;}
	void setUsername(const string& username){this->username=username;}
	string getUsername(){return this->username;}
	void setPassword(const string& password){this->password=password;}
	string getPassword(){return this->password;}
	void setDatabase(const string& database){this->database=database;}
	string getDatabase(){return this->database;}
	virtual ~DatabaseManager(void);
protected:
	string hostname;
	string username;
	string password;
	string database;
};

