/********************************************************************************
 * Class       : HttpResponse
 * Author      : Pi Ke
 * Date        : 2012-07-05
 * Version     : v1.0
 * Description : Http Response object, including the response status and source 
 *               code of the page
 ********************************************************************************/
#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H
#pragma once
#include <string>

class HttpResponse
{
public:
	HttpResponse(void);
	HttpResponse(HttpResponse& response);
	HttpResponse operator=(HttpResponse& response);
	~HttpResponse(void);

	void setResponseHeader(const std::string& responseHeader){this->responseHeader=responseHeader;}
	std::string getResponseHeader(){return this->responseHeader;}
	void setResponseCode(const std::string& responseCode){this->responseCode=responseCode;}
	std::string getReponseCode(){return this->responseCode;}
	void setSourceCode(const std::string& sourceCode){this->sourceCode=sourceCode;}
	std::string getSourceCode(){return this->sourceCode;}
	void setSourceCodeLength(const int sourceCodeLength){this->sourceCodeLength=sourceCodeLength;}
	int getSourceCodeLength(){return this->sourceCodeLength;}
	void setContentType(const std::string& contentType){this->contentType=contentType;}
	std::string getContentType(){return this->contentType;}
private:
	void copyData(HttpResponse& response);
private:
	std::string responseHeader;
	std::string responseCode;
	std::string sourceCode;
	int sourceCodeLength;
	std::string contentType;
};
#endif
