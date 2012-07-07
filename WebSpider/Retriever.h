/*****************************************************************************
 * @Author : Pi Ke
 * @Date : 2011-08-13
 * @Description : This class is a base class for other class. It is also an 
				  abstract class. To define the network programming functions 
				  such as connect,retrieve and close
 *****************************************************************************/
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Retriever
{
protected:
	string url;									//Url of the website
	string protocol;							//Protocol used such as HTTP or FTP
	string host;								//Host of the website. Format : http://127.0.0.1
	string path;								//Path of the webpage /dir/test.html
	string base;								//Base name of the web address
	string filename;							//Filename of the path
	int port;									//Port used by the server. Default is 80 or 8080
	string query;								//Query after the url's '?' mark. Format : key=value&key1=value1
public:
	Retriever(void);
	Retriever(string u){setUrl(u);parseUrl();}
	~Retriever(void);
	
	//Sets and gets
	void setUrl(string u){url=u;}
	string getUrl(){return url;}
	void setProtocol(string prot){protocol=prot;}
	string getProtocol(){return protocol;}
	void setHost(string h){host=h;}
	string getHost(){return host;}
	void setPath(string pt){path=pt;}
	string getPath(){return path;}
	void setBase(string b){base=b;}
	string getBase(){return base;}
	void setFulename(string f){filename=f;}
	string getFilename(){return filename;}
	void setPort(int p){port=p;}
	int getPort(){return port;}
	void setQuery(string q){query=q;}							//Query is the string after '?' mark format : key=value&key1=value1
	string getQuery(){return query;}

	//Define virtual functions
	virtual int initialize()=0;
	virtual int connect()=0;								    //Define web connect function
	//virtual int Connect(string url);
	virtual string retrieve()=0;
	virtual void close()=0;

	void parseUrl();
	void parseUrl(string url);									//Parse rhe given URL to protocol://host:port?query format
};

