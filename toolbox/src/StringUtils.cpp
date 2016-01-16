#include "toolbox/StringUtils.hpp"

#include <sstream>
#include <algorithm>

namespace toolbox {

//////////////////////////////////////////////////////////////////

std::vector<std::string> & split(const std::string &s, char delim, 
								 std::vector<std::string> &elems) 
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

////////////////////////////////////////////////////////////////

std::vector<std::string>& split(const std::string& input, const char* delims,
								std::vector <std::string>& tokens)
{
	std::size_t prev = 0, pos;
	while ((pos = input.find_first_of(delims, prev)) != std::string::npos)
	{
		if (pos > prev)
			tokens.push_back(input.substr(prev, pos-prev));
		prev = pos+1;
	}
	if (prev < input.length())
		tokens.push_back(input.substr(prev, std::string::npos));
    
    return tokens;
}

////////////////////////////////////////////////////////////////

std::vector<std::string> split(const std::string &s, char delim)
 {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

////////////////////////////////////////////////////////////////

void eraseWhiteSpace(std::string& str)
{
    str.erase (std::remove (str.begin(), str.end(), ' '), str.end());	
    str.erase (std::remove (str.begin(), str.end(), '\n'), str.end());	
    str.erase (std::remove (str.begin(), str.end(), '\t'), str.end());	
    str.erase (std::remove (str.begin(), str.end(), '\r'), str.end());
}

////////////////////////////////////////////////////////////////

void eraseAllChars(std::string& str, const char *chars_to_erase)
{
    if (!chars_to_erase)
        return;

	std::string toErase(chars_to_erase);
	
	std::string::iterator it;
	for(it  = toErase.begin();
		it != toErase.end();
		++it)
	{
		str.erase (std::remove (str.begin(), str.end(), *it), str.end());
	}
}


}
