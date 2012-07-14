/********************************************************************************
 * Class       : DatabaseConnection
 * Author      : Pi Ke
 * Date        : 2012-05-31
 * Version     : v1.0
 * Description : General database connection class to define database connection
 ********************************************************************************/
#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H
#pragma once
#include <string>
#include <vector>

class DatabaseConnection
{
public:
	DatabaseConnection(void);
	virtual void connect()=0;
	//virtual ResultSet* select(const string& sql)=0;
	virtual int update(const std::string& sql)=0;
	virtual void close()=0;

	void setHost(const std::string& host){this->host=host;}
	std::string getHost(){return this->host;}
	void setUsername(const std::string& username){this->username=username;}
	std::string getUsername(){return this->username;}
	void setPassword(const std::string& password){this->password=password;}
	std::string getPassword(){return this->password;}
	void setPort(const int& port){this->port=port;}
	int getPort(){return this->port;}
	void setDb(const std::string& db){this->db=db;}
	std::string getDb(){return this->db;}

	virtual ~DatabaseConnection(void);
private:
	std::string host;
	std::string username;
	std::string password;
	int port;
	std::string db;
};
#endif
