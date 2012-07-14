#include "WinRetriever.h"
#include "StringProcessor.h"
using namespace std;

WinRetriever::WinRetriever(void)
{
}


WinRetriever::~WinRetriever(void)
{
}

//Build the http request header
string WinRetriever::buildHttpRequest(){
	string req;
	req="GET ";

	if(path==""){
		req+="/ HTTP/1.1\r\nHost:";
	}else{
		req+=path;
		req+=" HTTP/1.1\r\nHost:";
	}

	req+=host+"\r\n";
	req+="User-Agent: WebSpider/1.0.1 (+http://pixelstech.net/)\r\n";				//User agent
	req+="Connection: close\r\n\r\n";												//Close
	
	return req;
}

int WinRetriever::initialize(){
	WSADATA wsaData;
	int err=WSAStartup(MAKEWORD(2,2),&wsaData);
	if(err!=0){
		cout<<"Error on WSAStartup()."<<endl;
		return -1;
	}

	parseUrl();											//Parse the URL
	return 1;
}

int WinRetriever::connect(){
	char ip[17];
	s_socket=socket(AF_INET,SOCK_STREAM,0);
	if(s_socket==INVALID_SOCKET){
		cout<<"Error at socket()."<<endl;
		return -1;
	}

	//Get the IP address of the target host
	struct hostent *host_struct;
	host_struct=gethostbyname(host.c_str());				//host.c_str() return a chat pointer
	if(host_struct==NULL){
		cout<<"Error on parsing the host name."<<endl;
		return -1;
	}

	memcpy(&socket_addr.sin_addr,host_struct->h_addr,host_struct->h_length);
	strcpy(ip,inet_ntoa(socket_addr.sin_addr));

	socket_addr.sin_family=AF_INET;
	socket_addr.sin_port=htons(80);
	socket_addr.sin_addr.s_addr=inet_addr(ip);

	if(::connect(s_socket,(SOCKADDR*)&socket_addr,sizeof(socket_addr))==SOCKET_ERROR){
		cout<<"connect() error ."<<endl;
		return -1;
	}

	string request=buildHttpRequest();
	if(send(s_socket,request.c_str(),request.length(),0)==SOCKET_ERROR){
		cout<<"Error on send()."<<endl;
		return -1;
	}

	return 0;
}

//Retrieve data from website
string WinRetriever::retrieve(){
	int bytes_recv=SOCKET_ERROR;
	char recv_buf[4096];
	int total_bytes=0;
	string str("");
	while((bytes_recv=recv(s_socket,recv_buf,1024,0))>0){
		recv_buf[bytes_recv]=0;
		total_bytes+=bytes_recv;
		string tmp_str(recv_buf);
		str+=tmp_str;
		memset(recv_buf,0,4096);
	}
	
	return StringProcessor::trim(str);
}

//Close the web retriever when all retrieving processes are
//finished
void WinRetriever::close(){
	 WSACleanup();
}