/********************************************************************************
 * Class       : PhraseManager
 * Author      : Pi Ke
 * Date        : 2012-07-07
 * Version     : v1.0
 * Description : Pharse manager to manage phrase entity
 ********************************************************************************/
#ifndef PHRASE_MANAGER_H
#define PHRASE_MANAGER_H
#pragma once
#include "databasemanager.h"
#include "Phrase.h"

class PhraseManager :
	public DatabaseManager
{
public:
	PhraseManager(void);
	~PhraseManager(void);

	vector<Phrase> getAllPhrases();
};
#endif
