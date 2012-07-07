#include "LinkManager.h"
#include "MySQLDatabaseConnection.h"
#include "StringProcessor.h"

LinkManager::LinkManager(void)
{
}

/************************************************************************
 * Method     : getLink()
 * Descrition : Get link from links table
 * Input      : Link Id
 * Output     : Link object
*************************************************************************/
Link LinkManager::getLink(const int linkId){
	Link link;
	/*
		MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
		conn->connect();

		string sql="SELECT * FROM links WHERE link_id="+linkId;
		ResultSet* rs=conn->select(sql);

		while(rs->next()){
			link.setLinkId(rs->getInt("link_id"));
			link.setUrl(rs->getString("url"));
			link.setTitle(rs->getString("title"));
			link.setFulltxt(rs->getString("fulltxt"));
			link.setMd5sum(rs->getString("md5sum"));
			link.setType(rs->getString("type"));
			link.setDomainId(rs->getInt("domain_id"));
		}
		conn->close();
		delete rs;
		delete conn;
	*/
	return link;
}

/************************************************************************
 * Method     : getLink()
 * Descrition : Get link from links table
 * Input      : Link URL
 * Output     : Link object
*************************************************************************/
Link LinkManager::getLink(const string& url){
	Link link;
	if(this->isExist(url)){
		MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
		conn->connect();

		string sql="SELECT * FROM links WHERE url='"+conn->escapeString(url)+"'";
		ResultSet* rs=conn->select(sql);

		while(rs->next()){
			link.setLinkId(rs->getInt("link_id"));
			link.setUrl(rs->getString("url"));
			link.setTitle(rs->getString("title"));
			link.setFulltxt(rs->getString("fulltxt"));
			link.setMd5sum(rs->getString("md5sum"));
			link.setType(rs->getString("type"));
			link.setDomainId(rs->getInt("domain_id"));
		}
		conn->close();
		delete rs;
		delete conn;
	}
	return link;
}

/************************************************************************
 * Method     : addLink()
 * Descrition : Add the Link object from Link table
 * Input      : A link object
 * Output     : void
*************************************************************************/
void LinkManager::addLink(Link& link){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="INSERT INTO links (url,title,fulltxt,md5sum,type,domain_id,indexdate) VALUES ('"+conn->escapeString(link.getUrl())+"','"+conn->escapeString(link.getTitle())+"','"+conn->escapeString(link.getFulltxt())+"','"+link.getMd5sum()+"','"+link.getType()+"',"+StringProcessor::intToString(link.getDomainId())+",now())";
	int ret=conn->update(sql);
	conn->close();
	delete conn;
}

/************************************************************************
 * Method     : isExist()
 * Descrition : Check whether a link exist in database or not
 * Input      : Link url
 * Output     : check statsu
*************************************************************************/
bool LinkManager::isExist(const string& url){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT 1 FROM links WHERE url='"+conn->escapeString(url)+"'";
	ResultSet* rs=conn->select(sql);

	bool exist=false;
	while(rs->next()){
		exist=true;
	}
	conn->close();
	delete conn;
	return exist;
}

LinkManager::~LinkManager(void)
{
}
