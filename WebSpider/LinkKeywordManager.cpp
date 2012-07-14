#include "LinkKeywordManager.h"
#include "MySQLDatabaseConnection.h"
#include "StringProcessor.h"
#include "md5.h"
using namespace std;
using namespace sql;

LinkKeywordManager::LinkKeywordManager(void)
{
}

/************************************************************************
 * Method     : getLinkKeyword()
 * Descrition : Get link keyword from links table
 * Input      : Link id and keyword
 * Output     : Link object
*************************************************************************/
LinkKeyword LinkKeywordManager::getLinkKeyword(int linkId,const string& keyword){
	LinkKeyword linkKeyword;
	/*
	if(this->isExist(linkId,keyword)){
		MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
		conn->connect();

		string sql="SELECT * FROM links WHERE url='"+url+"'";
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
	*/
	return linkKeyword;
}

/************************************************************************
 * Method     : addLinkKeyword()
 * Descrition : Add the Link object from Link table
 * Input      : A link object
 * Output     : void
*************************************************************************/
void LinkKeywordManager::addLinkKeyword(LinkKeyword& linkKeyword){
	string keyword=StringProcessor::trim(linkKeyword.getKeyword());
	if(keyword!=""){
		MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
		conn->connect();
		MD5 md5;
		char* keywordHash=md5.digestString(const_cast<char*>(keyword.c_str()));
		string firstChar(keywordHash);
		string sql="INSERT INTO link_keyword"+firstChar.substr(0,1)+" (link_id,keyword,weight) VALUES ("+StringProcessor::intToString(linkKeyword.getLinkId())+",'"+conn->escapeString(StringProcessor::trim(linkKeyword.getKeyword()))+"',"+StringProcessor::intToString(linkKeyword.getWeight())+")";
		int ret=conn->update(sql);
		conn->close();
		delete conn;
	}
}

/************************************************************************
 * Method     : deleteAll()
 * Descrition : Delete all link keywords from the database
 * Input      : void
 * Output     : Number of keywords deleted
*************************************************************************/
long LinkKeywordManager::deleteAll(){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();
	long num=0;

	for(int i=0;i<=15;++i){
		string sql="DELETE FROM link_keyword"+StringProcessor::intToHexChar(i);;
		num+=conn->update(sql);
	}
	
	conn->close();
	delete conn;
	return num;
}

/************************************************************************
 * Method     : deleteAll()
 * Descrition : Delete all link keywords of a URL from the database
 * Input      : linkId --The id of the link whose keywords to be deleted
 * Output     : Number of keywords deleted
*************************************************************************/
long LinkKeywordManager::deleteAll(int linkId){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();
	long num=0;
	
	for(int i=0;i<=15;++i){
		string sql="DELETE FROM link_keyword"+StringProcessor::intToHexChar(i)+" WHERE link_id="+StringProcessor::intToString(linkId);
		num+=conn->update(sql);
	}
	conn->close();
	delete conn;
	return num;
}

/************************************************************************
 * Method     : isExist()
 * Descrition : Check whether link keyword exists
 * Input      : linkId --The id of the link whose keywords to be checked
 *				keyword -- The keyword to be checked
 * Output     : Check result
*************************************************************************/
bool LinkKeywordManager::isExist(int linkId,const string& keyword){
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();
	MD5 md5;
	char* keywordHash=md5.digestString(const_cast<char*>(StringProcessor::trim(keyword).c_str()));
	string firstChar(keywordHash);
	string sql="SELECT 1 FROM link_keyword"+firstChar.substr(0,1)+" WHERE link_id="+StringProcessor::intToString(linkId)+" AND keyword='"+conn->escapeString(StringProcessor::trim(keyword))+"'";
	ResultSet* rs=conn->select(sql);

	bool exist=false;
	while(rs->next()){
		exist=true;
	}
	conn->close();
	delete conn;
	return exist;
}

LinkKeywordManager::~LinkKeywordManager(void)
{
}
