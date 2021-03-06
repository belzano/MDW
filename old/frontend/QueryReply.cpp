#include "QueryReply.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <map>
#include <iterator>

namespace WTF
{

Query::Query() { }

/////////////////////////////////////////////////////////////

void Query::setParsedData(const std::string& iKey, 
					  const char *data, size_t size, 
					  uint64_t offset)
{
	if (size <= 0)
		return;
				
	//std::cout << "  pushing data on key [" << iKey 
	//			<< "] : offset=" << offset 
	//			<< ", size="<< size << std::endl;

	std::map< std::string, std::shared_ptr< std::vector<char> > >::iterator it;
	
	it = _parsed_post_data.find(iKey);
	if (it == _parsed_post_data.end())
	{
		std::shared_ptr< std::vector<char> > newData = std::shared_ptr< std::vector<char> >(new std::vector<char>());
		it = _parsed_post_data.insert( std::make_pair(iKey, newData) ).first;
	}

				
	if (it->second->size() < size + offset)
		it->second->resize(size + offset);
			
	std::copy(data, data+size, it->second->begin()+offset);
}

//////////////////////////////////////////////////////////////////
	
void Query::pushRawData( const char *data, size_t size)
{
	if (size <= 0)
		return;
				
	//std::cout << "  pushing raw data: size="<< size << std::endl;
	
	if (_raw_post_data.get() == NULL)
		_raw_post_data = std::shared_ptr< std::vector<char> >(new std::vector<char>());
		
	uint64_t offset = _raw_post_data->size();
	
	_raw_post_data->resize(size + offset);
			
	std::copy(data, data+size, _raw_post_data->begin()+offset);	
}
	
//////////////////////////////////////////////////////////////////
	
Reply::Reply() 
{
	
}
	

}

