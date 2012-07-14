#include "HttpResponse.h"


HttpResponse::HttpResponse(void):contentType("")
{
}

HttpResponse::HttpResponse(HttpResponse& response){
	this->copyData(response);
}

HttpResponse HttpResponse::operator=(HttpResponse& response){
	if(this==&response){
		return *this;
	}

	this->copyData(response);

	return *this;
}

void HttpResponse::copyData(HttpResponse& response){
	this->responseCode=response.responseCode;
	this->responseHeader=response.responseHeader;
	this->sourceCode=response.sourceCode;
	this->sourceCodeLength=response.sourceCodeLength;
	this->contentType=response.getContentType();
}

HttpResponse::~HttpResponse(void)
{
}
