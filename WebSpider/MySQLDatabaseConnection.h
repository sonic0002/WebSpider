/********************************************************************************
 * Class       : MySQLDatabaseConnection
 * Author      : Pi Ke
 * Date        : 2012-05-31
 * Version     : v1.0
 * Description : MySQL database connection class to define database connection
 ********************************************************************************/
#ifndef MYSQL_DATABASE_CONNECTION_H
#define MYSQL_DATABASE_CONNECTION_H
#pragma once
// MySQL Connector/C++ specific headers 
#include <driver.h>
#include <connection.h>
#include <statement.h>
#include <resultset.h>
#include <metadata.h>
#include <resultset_metadata.h>
#include <exception.h>
#include <warning.h>
#include "databaseconnection.h"

class MySQLDatabaseConnection :public DatabaseConnection
{
public:
	MySQLDatabaseConnection(void);
	MySQLDatabaseConnection(const std::string& h,const std::string& u,const std::string& p);
	MySQLDatabaseConnection(const std::string& h,const std::string& u,const std::string& p,const std::string& b);
	MySQLDatabaseConnection(const MySQLDatabaseConnection& c);
	//MySQLDatabaseConnection operator=(const MySQLDatabaseConnection& c);
	void connect();
	sql::ResultSet* select(const std::string& sql);
	int update(const std::string& sql);
	void close();
	std::string escapeString(const std::string& str);
	~MySQLDatabaseConnection();
public:
	static int connCount;
private:
	void deleteStmt();
	void deleteConn();
private:
	static sql::Driver* driver;
	sql::Connection *conn;
	sql::Statement *stmt;
};
#endif