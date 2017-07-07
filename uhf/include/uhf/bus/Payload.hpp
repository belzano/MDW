#pragma once

#include "toolbox/Types.hpp"
#include <string>
#include <map>

namespace WTf
{
	
	//////////////////////////////////////////////////////////////
	
	class Payload 
	{
		public:
			toolbox::DataPtr m_rawData;
	};
	
	//////////////////////////////////////////////////////////////
	
	class PayloadHttp : public Payload
	{
		public:
			//setParsedData(const std::string& iKey, const char *data, size_t size, uint64_t offset);
								
			std::string m_url;
			std::map< std::string, toolbox::DataPtr > m_params;
	};
	
	//////////////////////////////////////////////////////////////

}

