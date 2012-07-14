/********************************************************************************
 * Class       : URL
 * Author      : Pi Ke
 * Date        : 2012-07-14
 * Version     : v1.0
 * Description : UTL to store information related to a URL, such as protocol, host,
 *				 port and path etc.
 ********************************************************************************/
#ifndef URL_H
#define URL_H
#pragma once
#include <string>

class URL
{
public:
	URL(void);
	URL(URL& urlObj);
	URL operator=(URL& url);
	~URL(void);

	//Sets and gets
	void setUrl(std::string url){this->url=url;}
	std::string getUrl(){return this->url;}
	void setProtocol(std::string protocol){this->protocol=protocol;}
	std::string getProtocol(){return this->protocol;}
	void setHost(std::string host){this->host=host;}
	std::string getHost(){return this->host;}
	void setPath(std::string path){this->path=path;}
	std::string getPath(){return this->path;}
	void setBase(std::string base){this->base=base;}
	std::string getBase(){return this->base;}
	void setFulename(std::string filename){this->filename=filename;}
	std::string getFilename(){return this->filename;}
	void setPort(int port){this->port=port;}
	int getPort(){return this->port;}
	void setQuery(std::string query){this->query=query;}							//Query is the string after '?' mark format : key=value&key1=value1
	std::string getQuery(){return this->query;}
private:
	void copyData(URL& urlObj);
private:
	std::string url;
	std::string protocol;
	std::string host;
	int port;
	std::string base;
	std::string path;
	std::string filename;
	std::string query;
};
#endif
