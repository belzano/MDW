#include "InvocationContextHTTP.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <map>
#include <iterator>

namespace WTF
{

/////////////////////////////////////////////////////////////

InvocationContextHTTP::InvocationContextHTTP(TriggerType iType) : InvocationContext(iType, 200)
{
	
}
		
/////////////////////////////////////////////////////////////

void InvocationContextHTTP::reply(Payload*)
{
	
}
		
/////////////////////////////////////////////////////////////
/*
void InvocationContextHTTP::setParsedData(	const std::string& iKey, 
											const char *data, size_t size, 
											uint64_t offset)
{
	if (size <= 0)
		return;

	std::map< std::string, toolbox::DataPtr >::iterator it;
	
	it = m_params.find(iKey);
	if (it == m_params.end())
	{
		toolbox::DataPtr newData(new toolbox::Data());
		it = m_params.insert( std::make_pair(iKey, newData) ).first;
	}
				
	if (it->second->size() < size + offset)
		it->second->resize(size + offset);
			
	std::copy(data, data+size, it->second->begin()+offset);
}
*/
}

