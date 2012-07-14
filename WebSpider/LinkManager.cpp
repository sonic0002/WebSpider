#include "LinkManager.h"
#include "MySQLDatabaseConnection.h"
#include "StringProcessor.h"
using namespace std;
using namespace sql;

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
			link.setLevel(rs->getInt("level"));
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

	string sql="INSERT INTO links (url,title,fulltxt,md5sum,type,domain_id,level,indexdate) VALUES ('"+conn->escapeString(link.getUrl())+"','"+conn->escapeString(link.getTitle())+"','"+conn->escapeString(link.getFulltxt())+"','"+link.getMd5sum()+"','"+link.getType()+"',"+StringProcessor::intToString(link.getDomainId())+","+StringProcessor::intToString(link.getLevel())+",now())";
	int ret=conn->update(sql);
	conn->close();
	delete conn;
}

/************************************************************************
 * Method     : updateLink()
 * Descrition : Update the given link
 * Input      : A link object
 * Output     : affected rows
*************************************************************************/
int LinkManager::updateLink(Link& link){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="UPDATE links SET title='"+conn->escapeString(link.getTitle())+"',fulltxt='"+conn->escapeString(link.getFulltxt())+"',md5sum='"+link.getMd5sum()+"',type='"+link.getType()+"',domain_id="+StringProcessor::intToString(link.getDomainId())+",level="+StringProcessor::intToString(link.getLevel())+",indexdate=NOW() WHERE url='"+conn->escapeString(link.getUrl())+"'";
	int ret=conn->update(sql);
	conn->close();
	delete conn;
	return ret;
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
	delete rs;
	delete conn;
	return exist;
}

/************************************************************************
 * Method     : deleteAll()
 * Descrition : Delete all indexed links from the database
 * Input      : void
 * Output     : Number of links deleted
*************************************************************************/
long LinkManager::deleteAll(){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="DELETE FROM links";
	long num=conn->update(sql);
	conn->close();
	delete conn;
	return num;
}

/************************************************************************
 * Method     : isContentChanged()
 * Descrition : Check whether content is changed or not
 * Input      : url -- Link url to be checked
 *				checksum -- The checksum to be checked
 * Output     : Check result
*************************************************************************/
bool LinkManager::isContentChanged(const string& url,const string& checksum){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT 1 FROM links WHERE url='"+conn->escapeString(url)+"' AND md5sum='"+checksum+"'";
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

LinkManager::~LinkManager(void)
{
}
