#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;

class StringProcessor
{
public:
	StringProcessor(void);
	~StringProcessor(void);

	static string trim(string str){
		string::size_type pos1 = str.find_first_not_of(' ');
		string::size_type pos2 = str.find_last_not_of(' ');
		str = str.substr(pos1 == string::npos ? 0 : pos1, 
			pos2 == string::npos ? str.length() - 1 : pos2 - pos1 + 1);

		return str;
	}

	static string toupper( const string &src ){
		string result;
		transform( src.begin(), src.end(), back_inserter( result ),::toupper);
		return result;
	}

	static string tolower( const string &src ){
		string result;
		transform( src.begin(), src.end(), back_inserter( result ),::tolower);
		return result;
	}

	static string intToString(const int i){
		std::ostringstream oss;
		oss<<i;
		// Return the underlying string
		return oss.str();
	}
	
	static bool beginWith(const string str,const string needle){
		return (str.find_first_of(needle)==0);
	}

	static bool endWith(const string str,const string needle){
		return (str.find_last_of(needle)==(str.length()-1));
	}

	static int substrCount(const string& str,const string& needle){
		int count(0);
		string::size_type substrPos(0);
		while(substrPos!=string::npos){
			substrPos=str.find(needle,substrPos);
			if(substrPos!=string::npos){
				++count;
				substrPos+=needle.length();
			}
		}
		return count;
	}
};


