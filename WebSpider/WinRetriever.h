#pragma once
#include "retriever.h"
#include <iostream>
#include <WinSock2.h>
#pragma comment(linker,"/defaultlib:ws2_32.lib")
using namespace std;

class WinRetriever :
	public Retriever
{
private:
	SOCKET s_socket;
	SOCKADDR_IN socket_addr;
protected:
	string buildHttpRequest();
public:
	WinRetriever(void);
	WinRetriever(string url):Retriever(url){};
	~WinRetriever(void);

	//Sets and gets
	void setSocket(SOCKET sock){s_socket=sock;}
	SOCKET getSocket(){return s_socket;}
	void setSocketAddress(SOCKADDR_IN si){socket_addr=si;}
	SOCKADDR_IN getSocketAddress(){return socket_addr;}

	int initialize();
	int connect();
	string retrieve();
	void close();
};


