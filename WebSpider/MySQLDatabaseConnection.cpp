#include "MySQLDatabaseConnection.h"
#include <regex>

Driver* MySQLDatabaseConnection::driver=get_driver_instance();

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
		throw;
		//return nullptr;
	}
}

int MySQLDatabaseConnection::update(const string& sql){
	try{
		stmt=conn->createStatement();
		return stmt->executeUpdate(sql);
	}catch(SQLException &ex){
		cout<<"Exception in update() of "<<__FILE__;
		cout<<"Error : "<<ex.what();
		throw;
		//return nullptr;
	}
}

void MySQLDatabaseConnection::close(){
	try{
		stmt->close();
		conn->close();
	}catch(SQLException &ex){
		cout<<"Exception in close() of "<<__FILE__;
		cout<<"Error : "<<ex.what();
		throw;
	}
}

string MySQLDatabaseConnection::escapeString(const string& str){
    /*
	using namespace std::tr1;
	regex rg("\r|\n|\'");
	string replacement(" ");
	string plainText=regex_replace(str,rg,replacement);
	return plainText;
	*/
	std::size_t n = str.length();
    std::string escaped;
    escaped.reserve(n * 2);        // pessimistic preallocation

    for (std::size_t i = 0; i < n; ++i) {
        if (str[i] == '\\' || str[i] == '\'')
            escaped += '\\';
        escaped += str[i];
    }
    return escaped;
}

MySQLDatabaseConnection::~MySQLDatabaseConnection()
{
	if(stmt){
		try{
			delete stmt;
		}catch(SQLException &ex){
			cout<<"Exception in close() of "<<__FILE__;
			cout<<"Error : "<<ex.what();
		}
	}
	if(conn){
		try{
			delete conn;
		}catch(SQLException &ex){
			cout<<"Exception in close() of "<<__FILE__;
			cout<<"Error : "<<ex.what();
		}
	}
}
