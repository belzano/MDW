#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace toolbox
{

//////////////////////////////////////////////////////////////////////

template <class T>
std::string ToString(const T& iVal)
{
	std::stringstream stream;
	stream << iVal;
	return stream.str();
}

//////////////////////////////////////////////////////////////////

std::vector<std::string>& split(const std::string &s, char delim, 
								std::vector<std::string> &elems);

std::vector<std::string>& split(const std::string& input, const char* delims, 
								std::vector<std::string>& tokens);
				
std::vector<std::string> split(const std::string &s, char delim);
									
void eraseWhiteSpace(std::string& input);
   
void eraseAllChars(std::string& input, const char *chars_to_erase);
 
	
}


