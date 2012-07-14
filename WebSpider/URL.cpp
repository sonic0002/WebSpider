#include "URL.h"


URL::URL(void):url(""),protocol(""),host(""),port(80),base(""),filename(""),path(""),query("")
{
}

URL::URL(URL& urlObj){
	this->copyData(urlObj);
}

URL URL::operator=(URL& urlObj){
	if(this==&urlObj){
		return *this;
	}

	this->copyData(urlObj);
	return *this;
}

void URL::copyData(URL& urlObj){
	this->url=urlObj.getUrl();
	this->host=urlObj.getHost();
	this->port=urlObj.getPort();
	this->path=urlObj.getPath();
	this->base=urlObj.getBase();
	this->filename=urlObj.getFilename();
	this->query=urlObj.getQuery();
}

URL::~URL(void)
{
}
