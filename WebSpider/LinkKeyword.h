/********************************************************************************
 * Class       : LinkKeyword
 * Author      : Pi Ke
 * Date        : 2012-07-01
 * Version     : v1.0
 * Description : Link keyword entity
 ********************************************************************************/
#pragma once
#include <string>

class LinkKeyword
{
public:
	LinkKeyword(void);
	~LinkKeyword(void);

	void setLinkId(const int linkId){this->linkId=linkId;}
	int getLinkId(){return this->linkId;}
	void setKeyword(const std::string& keyword){this->keyword=keyword;}
	std::string getKeyword(){return this->keyword;}
	void setWeight(const int weight){this->weight=weight;}
	int getWeight(){return this->weight;}
private:
	int linkId;
	std::string keyword;
	int weight;
};

