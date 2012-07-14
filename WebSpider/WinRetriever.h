/*****************************************************************************
 * Class       : WinRetriever
 * Author      : Pi Ke
 * Date        : 2011-08-13
 * Version     : v1.0
 * Description : This class is a derived class. To define the network programming 
 *				 functions such as connect,retrieve and close. They are using
 *				 Windows specified network libraries
 *****************************************************************************/
#ifndef WIN_RETRIEVER_H
#define WIN_RETRIEVER_H
#pragma once
#include <string>
#include "retriever.h"
#include <iostream>
#include <WinSock2.h>
#pragma comment(linker,"/defaultlib:ws2_32.lib")

class WinRetriever :
	public Retriever
{
private:
	SOCKET s_socket;
	SOCKADDR_IN socket_addr;
protected:
	std::string buildHttpRequest();
public:
	WinRetriever(void);
	WinRetriever(std::string url):Retriever(url){};
	~WinRetriever(void);

	//Sets and gets
	void setSocket(SOCKET sock){s_socket=sock;}
	SOCKET getSocket(){return s_socket;}
	void setSocketAddress(SOCKADDR_IN si){socket_addr=si;}
	SOCKADDR_IN getSocketAddress(){return socket_addr;}

	int initialize();
	int connect();
	std::string retrieve();
	void close();
};
#endif

