/********************************************************************************
 * Class       : Phrase
 * Author      : Pi Ke
 * Date        : 2012-07-07
 * Version     : v1.0
 * Description : Phrase entity to map to the phrases table in database
 ********************************************************************************/
#ifndef PHRASE_H
#define PHRASE_H
#pragma once
#include <string>
using namespace std;

class Phrase
{
public:
	Phrase(void);
	~Phrase(void);
	
	void setPhraseId(const int phraseId){this->phraseId=phraseId;}
	int getPhraseId(){return this->phraseId;}
	void setPhrase(const string& phrase){this->phrase=phrase;}
	string getPhrase(){return this->phrase;}
private:
	int phraseId;
	string phrase;
};
#endif
