#include <iostream>
#include "Retriever.h"
#include "StringProcessor.h"

Retriever::Retriever(void)
{
}

Retriever::~Retriever(void)
{
}

/*************************************************************************
 * @parameter : url
 * @description : parse rhe given URL to protocol://host:port?query format
 *************************************************************************/
void Retriever::parseUrl(){
	parseUrl(url);
}

/*************************************************************************
 * @parameter : url
 * @description : parse rhe given URL to protocol://host:port?query format
 *************************************************************************/
void Retriever::parseUrl(string u){
	url=StringProcessor::trim(u);								//Trim the URL,remove white spaces
	string::size_type delim_pos=url.find("://");				//Find :// in the url
	
	//Get protocol
	if(delim_pos!=string::npos){
		protocol=url.substr(0,delim_pos);						//Set the protocol
	}else{
		protocol="";
	}

	//Get host
	string::size_type port_delim_pos=string::npos;;				//Port delimiter position
	string::size_type path_delim_pos=string::npos;;				//Path delimiter position
	if(delim_pos!=string::npos){			
		port_delim_pos=url.find(':',delim_pos+1);
		path_delim_pos=url.find('/',delim_pos+3);	
		//If port is specified
		if(port_delim_pos!=string::npos){
			host=url.substr(delim_pos+3,port_delim_pos-delim_pos-3);
		}else{		//Port is not specified
			if(path_delim_pos!=string::npos){	//path is specified
				host=url.substr(delim_pos+3,path_delim_pos-delim_pos-3);
			}else{
				host=url.substr(delim_pos+3);
			}
		}
	}else{	// ://notspecified
		port_delim_pos=url.find(':');
		path_delim_pos=url.find('/');	
		//If port is specified
		if(port_delim_pos!=string::npos){
			host=url.substr(0,port_delim_pos);
		}else{		//Port is not specified
			if(path_delim_pos!=string::npos){	//path is specified
				host=url.substr(0,path_delim_pos);
			}else{
				host=url.substr(0,url.length());
			}
		}
	}

	//Get port
	if(port_delim_pos!=string::npos){
		if(path_delim_pos!=string::npos){
			port=atoi(url.substr(port_delim_pos+1,path_delim_pos-port_delim_pos-1).c_str());
		}else{
			port=atoi(url.substr(port_delim_pos+1,url.length()-port_delim_pos-1).c_str());
		}
	}else{
		port=80;
	}

	//Get path
	string::size_type query_delim_pos=url.find_first_of('?');
	if(path_delim_pos!=string::npos){
		if(query_delim_pos!=string::npos){
			path=url.substr(path_delim_pos,query_delim_pos-path_delim_pos);
		}else{
			path=url.substr(path_delim_pos,url.length()-path_delim_pos);
		}
	}else{
		path="";
	}

	//Get base name
	string::size_type filename_delim=path.find_last_of("/");
	if(filename_delim!=string::npos){
		base=path.substr(0,filename_delim+1);
	}else{
		base="";
	}

	//Get filename
	if(filename_delim!=string::npos){
		filename=path.substr(filename_delim+1);
	}else{
		filename=path;
	}

	//Get query
	if(query_delim_pos!=string::npos){
		query=url.substr(query_delim_pos+1,url.length()-query_delim_pos-1);
	}else{
		query="";
	}
}
