/********************************************************************************
 * Class       : DatabaseConnection
 * Author      : Pi Ke
 * Date        : 2012-05-31
 * Version     : v1.0
 * Description : General database connection class to define database connection
 ********************************************************************************/
#pragma once
#include <string>
#include <vector>
using namespace std;

class DatabaseConnection
{
public:
	DatabaseConnection(void);
	virtual void connect()=0;
	//virtual ResultSet* select(const string& sql)=0;
	virtual int update(const string& sql)=0;
	virtual void close()=0;

	void setHost(const string& host){this->host=host;}
	string getHost(){return this->host;}
	void setUsername(const string& username){this->username=username;}
	string getUsername(){return this->username;}
	void setPassword(const string& password){this->password=password;}
	string getPassword(){return this->password;}
	void setPort(const int& port){this->port=port;}
	int getPort(){return this->port;}
	void setDb(const string& db){this->db=db;}
	string getDb(){return this->db;}

	virtual ~DatabaseConnection(void);
private:
	string host;
	string username;
	string password;
	int port;
	string db;
};

