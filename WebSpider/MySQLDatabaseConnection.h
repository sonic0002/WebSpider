/********************************************************************************
 * Class       : MySQLDatabaseConnection
 * Author      : Pi Ke
 * Date        : 2012-05-31
 * Version     : v1.0
 * Description : MySQL database connection class to define database connection
 ********************************************************************************/
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

using namespace sql;

class MySQLDatabaseConnection :public DatabaseConnection
{
public:
	MySQLDatabaseConnection(void);
	MySQLDatabaseConnection(const string& h,const string& u,const string& p);
	MySQLDatabaseConnection(const string& h,const string& u,const string& p,const string& b);
	MySQLDatabaseConnection(const MySQLDatabaseConnection& c);
	//MySQLDatabaseConnection operator=(const MySQLDatabaseConnection& c);
	void connect();
	ResultSet* select(const string& sql);
	int update(const string& sql);
	void close();
	string escapeString(const string& str);
	~MySQLDatabaseConnection();
private:
	static Driver* driver;
	Connection *conn;
	Statement *stmt;
};
