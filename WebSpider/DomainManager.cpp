#include "DomainManager.h"
#include "MySQLDatabaseConnection.h"
using namespace std;
using namespace sql;

DomainManager::DomainManager(void)
{
}

/************************************************************************
 * Method     : getAllDomains()
 * Descrition : Get all Domain object from Domian table
 * Input      : void
 * Output     : A list of domain objects
*************************************************************************/
vector<Domain> DomainManager::getAllDomains(){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT * FROM domains";
	ResultSet* rs=conn->select(sql);

	vector<Domain> domains;
	while(rs->next()){
		Domain domain;
		domain.setDomainId(rs->getInt("domain_id"));
		domain.setUrl(rs->getString("url"));
		domain.setStatus(rs->getString("status"));
		domains.push_back(domain);
	}
	conn->close();
	delete rs;
	delete conn;
	return domains;
}

/************************************************************************
 * Method     : getAllowedDomains()
 * Descrition : Get allowed Domain object from Domian table
 * Input      : void
 * Output     : A list of allowed domain objects
*************************************************************************/
vector<Domain> DomainManager::getAllowedDomains(){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT * FROM domains WHERE status='allowed'";
	ResultSet* rs=conn->select(sql);

	vector<Domain> domains;
	while(rs->next()){
		Domain domain;
		domain.setDomainId(rs->getInt("domain_id"));
		domain.setUrl(rs->getString("url"));
		domain.setStatus(rs->getString("status"));
		domains.push_back(domain);
	}
	conn->close();
	delete rs;
	delete conn;
	return domains;
}

/************************************************************************
 * Method     : getBlockedDomains()
 * Descrition : Get blocked Domain object from Domian table
 * Input      : void
 * Output     : A list of blocked domain objects
*************************************************************************/
vector<Domain> DomainManager::getBlockedDomains(){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT * FROM domains WHERE status='blocked'";
	ResultSet* rs=conn->select(sql);

	vector<Domain> domains;
	while(rs->next()){
		Domain domain;
		domain.setDomainId(rs->getInt("domain_id"));
		domain.setUrl(rs->getString("url"));
		domain.setStatus(rs->getString("status"));
		domains.push_back(domain);
	}
	conn->close();
	delete rs;
	delete conn;
	return domains;
}

/************************************************************************
 * Method     : getDomain()
 * Descrition : Get domain from the domains table
 * Input      : Domain url
 * Output     : Domain
*************************************************************************/
Domain DomainManager::getDomain(const string& url){
	Domain domain;
	if(this->isExist(url)){
		MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
		conn->connect();

		string sql="SELECT * FROM domains WHERE url='"+url+"'";
		ResultSet* rs=conn->select(sql);

		while(rs->next()){
			domain.setDomainId(rs->getInt("domain_id"));
			domain.setUrl(rs->getString("url"));
			domain.setStatus(rs->getString("status"));
		}
		conn->close();
		delete rs;
		delete conn;
	}
	return domain;
}

/************************************************************************
 * Method     : addDomain()
 * Descrition : Add the Domain object from Domian table
 * Input      : A domain object
 * Output     : void
*************************************************************************/
void DomainManager::addDomain(Domain& domain){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="INSERT INTO domains (url,status) VALUES ('"+domain.getUrl()+"','"+domain.getStatus()+"')";
	int ret=conn->update(sql);
	conn->close();
	delete conn;
}

/************************************************************************
 * Method     : isExist()
 * Descrition : Check whether a domain exist in database or not
 * Input      : Domain url
 * Output     : check statsu
*************************************************************************/
bool DomainManager::isExist(const string& url){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT 1 FROM domains WHERE url='"+url+"'";
	ResultSet* rs=conn->select(sql);

	bool exist=false;
	while(rs->next()){
		exist=true;
	}
	conn->close();
	delete rs;
	delete conn;
	return exist;
}

DomainManager::~DomainManager(void)
{
}
