#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>

#include "toolbox/Types.hpp"

namespace uhf
{

#define GET             0
#define POST            1

	class Query
	{
		
	public:
		Query();

		void setParsedData( const std::string& iKey,
							const char *data, size_t size, uint64_t offset);
		
		void pushRawData( const char *data, size_t size);
	
		int connectiontype;
		
		std::string _url;
		//std::string _url_verb;
		//std::list<std::string> _url_path;
		std::map<std::string, std::string>  _url_args;
		 
		std::string _post_filename;
		
		toolbox::DataPtr _raw_post_data;
		std::map< std::string, toolbox::DataPtr > _parsed_post_data;
	};



	class Reply
	{
	public:
		Reply();
	
		toolbox::DataPtr answerstring;
		int answercode;
	};

}

