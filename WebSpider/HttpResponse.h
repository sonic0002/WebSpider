/********************************************************************************
 * Class       : HttpResponse
 * Author      : Pi Ke
 * Date        : 2012-07-05
 * Version     : v1.0
 * Description : Http Response object, including the response status and source 
 *               code of the page
 ********************************************************************************/
#pragma once
#include <string>
using namespace std;

class HttpResponse
{
public:
	HttpResponse(void);
	HttpResponse(HttpResponse& response);
	HttpResponse operator=(HttpResponse& response);
	~HttpResponse(void);

	void setResponseHeader(const string& responseHeader){this->responseHeader=responseHeader;}
	string getResponseHeader(){return this->responseHeader;}
	void setResponseCode(const string& responseCode){this->responseCode=responseCode;}
	string getReponseCode(){return this->responseCode;}
	void setSourceCode(const string& sourceCode){this->sourceCode=sourceCode;}
	string getSourceCode(){return this->sourceCode;}
	void setSourceCodeLength(const int sourceCodeLength){this->sourceCodeLength=sourceCodeLength;}
	int getSourceCodeLength(){return this->sourceCodeLength;}

private:
	string responseHeader;
	string responseCode;
	string sourceCode;
	int sourceCodeLength;
};

