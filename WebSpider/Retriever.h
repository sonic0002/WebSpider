/*****************************************************************************
 * Class       : Retriever
 * Author      : Pi Ke
 * Date        : 2011-08-13
 * Version     : v1.0
 * Description : This class is a base class for other class. It is also an 
				 abstract class. To define the network programming functions 
				 such as connect,retrieve and close
 *****************************************************************************/
#ifndef RETRIEVER_H
#define RETRIEVER_H
#pragma once
#include <iostream>
#include <string>

class Retriever
{
protected:
	std::string url;									//Url of the website
	std::string protocol;							//Protocol used such as HTTP or FTP
	std::string host;								//Host of the website. Format : http://127.0.0.1
	std::string path;								//Path of the webpage /dir/test.html
	std::string base;								//Base name of the web address
	std::string filename;							//Filename of the path
	int port;									//Port used by the server. Default is 80 or 8080
	std::string query;								//Query after the url's '?' mark. Format : key=value&key1=value1
public:
	Retriever(void);
	Retriever(std::string u){setUrl(u);parseUrl();}
	~Retriever(void);
	
	//Sets and gets
	void setUrl(std::string u){url=u;}
	std::string getUrl(){return url;}
	void setProtocol(std::string prot){protocol=prot;}
	std::string getProtocol(){return protocol;}
	void setHost(std::string h){host=h;}
	std::string getHost(){return host;}
	void setPath(std::string pt){path=pt;}
	std::string getPath(){return path;}
	void setBase(std::string b){base=b;}
	std::string getBase(){return base;}
	void setFulename(std::string f){filename=f;}
	std::string getFilename(){return filename;}
	void setPort(int p){port=p;}
	int getPort(){return port;}
	void setQuery(std::string q){query=q;}							//Query is the string after '?' mark format : key=value&key1=value1
	std::string getQuery(){return query;}

	//Define virtual functions
	virtual int initialize()=0;
	virtual int connect()=0;								    //Define web connect function
	//virtual int Connect(string url);
	virtual std::string retrieve()=0;
	virtual void close()=0;

	void parseUrl();
	void parseUrl(std::string url);									//Parse rhe given URL to protocol://host:port?query format
};
#endif
