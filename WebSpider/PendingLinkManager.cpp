#include "PendingLinkManager.h"
#include "MySQLDatabaseConnection.h"
#include "StringProcessor.h"
using namespace std;
using namespace sql;

PendingLinkManager::PendingLinkManager(void)
{
}

/************************************************************************
 * Method     : addPendingLink()
 * Descrition : Add the PendingLink object to link_pending table
 * Input      : A PendingLink object
 * Output     : void
*************************************************************************/
void PendingLinkManager::addPendingLink(PendingLink& pendingLink){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="INSERT INTO link_pending (url,domain_id,level) VALUES ('"+conn->escapeString(pendingLink.getUrl())+"',"+StringProcessor::intToString(pendingLink.getDomainId())+","+StringProcessor::intToString(pendingLink.getLevel())+")";
	int ret=conn->update(sql);
	conn->close();
	delete conn;
}

/************************************************************************
 * Method     : isExist()
 * Descrition : Check whether a link exist in link_pending or not
 * Input      : Link url
 * Output     : check statsu
*************************************************************************/
bool PendingLinkManager::isExist(const string& url){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT 1 FROM link_pending WHERE url='"+conn->escapeString(url)+"'";
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

/************************************************************************
 * Method     : getAllPendingLink()
 * Descrition : Get all pending links from pending link table
 * Input      : void
 * Output     : A list of pending links
*************************************************************************/
vector<PendingLink> PendingLinkManager::getAllPendingLink(){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT * FROM link_pending";
	ResultSet* rs=conn->select(sql);

	vector<PendingLink> pendingLinks;
	while(rs->next()){
		PendingLink pendingLink;
		pendingLink.setDomainId(rs->getInt("domain_id"));
		pendingLink.setUrl(rs->getString("url"));
		pendingLink.setLevel(rs->getInt("level"));
		pendingLinks.push_back(pendingLink);
	}
	conn->close();
	delete rs;
	delete conn;
	return pendingLinks;
}

/************************************************************************
 * Method     : deletePendingLink()
 * Descrition : Delete a pending link from pending link table
 * Input      : Link URL
 * Output     : void
*************************************************************************/
void PendingLinkManager::deletePendingLink(const string& url){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="DELETE FROM link_pending WHERE url='"+conn->escapeString(url)+"'";
	int ret=conn->update(sql);
	conn->close();
	delete conn;
}

/************************************************************************
 * Method     : deleteAll()
 * Descrition : Delete all pending links from the database
 * Input      : void
 * Output     : Number of links deleted
*************************************************************************/
long PendingLinkManager::deleteAll(){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="DELETE FROM link_pending";
	long num=conn->update(sql);
	conn->close();
	delete conn;
	return num;
}

PendingLinkManager::~PendingLinkManager(void)
{
}
