/********************************************************************************
 * Class       : Configure
 * Author      : Pi Ke
 * Date        : 2012-07-08
 * Version     : v1.0
 * Description : Configure class to store the program configurartion parameters
 ********************************************************************************/
#ifndef CONFIGURE_H
#define CONFIGURE_H
#pragma once
#include <string>
using namespace std;

class Configure
{
public:
	Configure(void);
	~Configure(void);
	
	//Can webspider leave the current domain
	static bool canLeaveDomain;
	
	//Start hostname to index
	static string hostname;

	//Index level
	static int level;

	//Reindex : Whether reindex or not
	static bool reindex;
};
#endif

