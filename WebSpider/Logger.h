#pragma once
#include <iostream>
#include <string>

class Logger
{
public:
	Logger(void);
	static void log(const std::string& msg){
		std::cout<<msg<<std::endl;
	}
	virtual ~Logger(void);
};

