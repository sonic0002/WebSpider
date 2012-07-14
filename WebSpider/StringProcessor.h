/*****************************************************************************
 * Class       : StringProcessor
 * Author      : Pi Ke
 * Date        : 2011-07-10
 * Version     : v1.0
 * Description : This class is to process std string objects. Including int to 
 *				 string, uppercase etc
 *****************************************************************************/
#ifndef STRING_PROCESSOR_H
#define STRING_PROCESSOR_H
#pragma once
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>

class StringProcessor
{
public:
	StringProcessor(void);
	~StringProcessor(void);

	static std::string trim(std::string str){
		std::string::size_type pos1 = str.find_first_not_of(' ');
		std::string::size_type pos2 = str.find_last_not_of(' ');
		str = str.substr(pos1 == std::string::npos ? 0 : pos1, 
			pos2 == std::string::npos ? str.length() - 1 : pos2 - pos1 + 1);

		return str;
	}

	static std::string toupper( const std::string &src ){
		std::string result;
		transform( src.begin(), src.end(), back_inserter( result ),::toupper);
		return result;
	}

	static std::string tolower( const std::string &src ){
		std::string result;
		transform( src.begin(), src.end(), back_inserter( result ),::tolower);
		return result;
	}

	static std::string intToString(const int i){
		std::ostringstream oss;
		oss<<i;
		// Return the underlying string
		return oss.str();
	}
	
	static bool beginWith(const std::string str,const std::string needle){
		return (!str.compare(0,needle.length(),needle));
	}

	static bool endWith(const std::string str,const std::string needle){
		if (str.length() >= needle.length()) {
			return (0 == str.compare (str.length() - needle.length(), needle.length(), needle));
		} 
        return false;
	}

	static int substrCount(const std::string& str,const std::string& needle){
		int count(0);
		std::string::size_type substrPos(0);
		while(substrPos!=std::string::npos){
			substrPos=str.find(needle,substrPos);
			if(substrPos!=std::string::npos){
				++count;
				substrPos+=needle.length();
			}
		}
		return count;
	}

	static int StringProcessor::parseInt(const std::string& str){
		return atoi(str.c_str());
	}

	template< typename T >
	static std::string intToHexStr( T i ){
		std::stringstream stream;
		stream << "0x" 
				<< std::setfill ('0') << std::setw(sizeof(T)*2) 
				<< std::hex << i;
		return stream.str();
	}

	template< typename T >
	static std::string intToHexChar( T i ){
		std::stringstream stream;
		stream  << std::setw(1) 
				<< std::hex << i;
		return stream.str();
	}
};
#endif

