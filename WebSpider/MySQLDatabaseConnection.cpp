#include "MySQLDatabaseConnection.h"
#include <regex>
using namespace std;
using namespace sql;

Driver* MySQLDatabaseConnection::driver=get_driver_instance();
int MySQLDatabaseConnection::connCount=0;

MySQLDatabaseConnection::MySQLDatabaseConnection(void)
{
}

MySQLDatabaseConnection::MySQLDatabaseConnection(const string& h,const string& u,const string& p):stmt(NULL),conn(NULL)
{
	this->setHost(h);
	this->setUsername(u);
	this->setPassword(p);
}

MySQLDatabaseConnection::MySQLDatabaseConnection(const string& h,const string& u,const string& p,const string& b):stmt(NULL),conn(NULL)
{
	this->setHost(h);
	this->setUsername(u);
	this->setPassword(p);
	this->setDb(b);
}

void MySQLDatabaseConnection::connect(){
	try{
		//Create a database connection
		conn = driver->connect(this->getHost(),this->getUsername(),this->getPassword());
		conn->setSchema(this->getDb());
	}catch(SQLException &ex){
		cout<<"Exception in connect() of "<<__FILE__<<endl;
		cout<<"Error : "<<ex.what()<<endl;
		this->close();
		this->deleteConn();
		throw;
	}
}

ResultSet* MySQLDatabaseConnection::select(const string& sql){
	try{
		//Create a statement object
		stmt=conn->createStatement();
		ResultSet *res=stmt->executeQuery(sql);
		return res;
	}catch(SQLException &ex){
		cout<<"Exception in select() of "<<__FILE__;
		cout<<"Error : "<<ex.what();
		this->close();
		this->deleteStmt();
		this->deleteConn();
		throw;
	}
}

int MySQLDatabaseConnection::update(const string& sql){
	try{
		//Create a statement object
		stmt=conn->createStatement();
		int num=stmt->executeUpdate(sql);
		this->deleteStmt();						//Here need to delete the stmt
		return num;
		//return stmt->executeUpdate(sql);
	}catch(SQLException &ex){
		cout<<"Exception in update() of "<<__FILE__;
		cout<<"Error : "<<ex.what();
		this->close();
		this->deleteStmt();
		this->deleteConn();
		throw;
		//return nullptr;
	}
}

void MySQLDatabaseConnection::close(){
	try{
		if(conn){
			conn->close();
		}
	}catch(SQLException &ex){
		cout<<"Exception in close() of "<<__FILE__;
		cout<<"Error : "<<ex.what();
		this->deleteStmt();
		this->deleteConn();
		throw;
	}
}

string MySQLDatabaseConnection::escapeString(const string& str){
	std::size_t n = str.length();
    std::string escaped;
    escaped.reserve(n * 2);        // pessimistic preallocation

    for (std::size_t i = 0; i < n; ++i) {
        if (str[i] == '\\' || str[i] == '\''){
            escaped += '\\';
		}
        escaped += str[i];
    }
    return escaped;
}

void MySQLDatabaseConnection::deleteStmt(){
	if(stmt){
		try{
			delete stmt;
			stmt=NULL;
		}catch(SQLException &ex){
			cout<<"Exception in close() of "<<__FILE__;
			cout<<"Error : "<<ex.what();
		}
	}
}

void MySQLDatabaseConnection::deleteConn(){
	if(conn){
		try{
			delete conn;
			conn=NULL;
		}catch(SQLException &ex){
			cout<<"Exception in deleteConn() of "<<__FILE__;
			cout<<"Error : "<<ex.what();
		}
	}
}

MySQLDatabaseConnection::~MySQLDatabaseConnection()
{
	this->deleteStmt();
	this->deleteConn();
}
