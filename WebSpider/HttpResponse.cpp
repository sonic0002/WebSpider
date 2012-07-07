#include "HttpResponse.h"


HttpResponse::HttpResponse(void)
{
}

HttpResponse::HttpResponse(HttpResponse& response){
	this->responseCode=response.responseCode;
	this->responseHeader=response.responseHeader;
	this->sourceCode=response.sourceCode;
	this->sourceCodeLength=response.sourceCodeLength;
}

HttpResponse HttpResponse::operator=(HttpResponse& response){
	if(this==&response){
		return *this;
	}

	this->responseCode=response.responseCode;
	this->responseHeader=response.responseHeader;
	this->sourceCode=response.sourceCode;
	this->sourceCodeLength=response.sourceCodeLength;

	return *this;
}

HttpResponse::~HttpResponse(void)
{
}
