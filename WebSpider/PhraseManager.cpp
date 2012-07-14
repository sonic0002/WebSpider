#include "PhraseManager.h"
#include "MySQLDatabaseConnection.h"
using namespace sql;

PhraseManager::PhraseManager(void)
{
}

/************************************************************************
 * Method     : getAllPhrases()
 * Descrition : Get all phrases from the database
 * Input      : void
 * Output     : Phrase object list
*************************************************************************/
vector<Phrase> PhraseManager::getAllPhrases(){
	vector<Phrase> phraseList;
	MySQLDatabaseConnection* conn=new MySQLDatabaseConnection(this->hostname,this->username,this->password,this->database);
	conn->connect();

	string sql="SELECT * FROM phrases";
	ResultSet* rs=conn->select(sql);

	while(rs->next()){
		Phrase phrase;
		phrase.setPhraseId(rs->getInt("phrase_id"));
		phrase.setPhrase(rs->getString("phrase"));
		phraseList.push_back(phrase);
	}
	conn->close();
	delete rs;
	delete conn;

	return phraseList;
}

PhraseManager::~PhraseManager(void)
{
}
