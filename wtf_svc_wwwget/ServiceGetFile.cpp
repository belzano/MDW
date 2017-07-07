#include "ServiceGetFile.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

#include "toolbox/StringUtils.hpp"
#include "toolbox/Logger.hpp"
#include "toolbox/ExecutionContext.hpp"


ServiceGetFile::ServiceGetFile() : WTF::ServiceTemplate<ServiceGetFile>()
{
 
}

//////////////////////////////////////////////////////////////////////3

bool ServiceGetFile::process(const std::string url,
							const std::map<std::string, std::string>& , 			 
							const std::map<std::string, toolbox::DataPtr>& ,
							toolbox::DataPtr& response)
{
	MDW_LOG_DEBUG("ServiceGetFile[" << url << "]");
	
	// get the root path		
	std::string rootPath = "";
	std::map<std::string, std::string>::const_iterator it = getContext().getStaticParameters().find("rootpath");
	if (it != getContext().getStaticParameters().end())	
		rootPath += toolbox::ExecutionContext::instance().getDirData() + it->second;
	else	
		rootPath += "/www";
		
	// transform empty url to index.html
	std::string theUrl = url;
	if	(theUrl.empty() || theUrl == "/")	
		theUrl = "/index.html";
		
	// try to get the file	
	std::ifstream file(rootPath + theUrl);
	
	// if no file return false;
	if (! file.is_open())
	{
		response = toolbox::MakeDataPtr("file not found");
		return true;
	}
	
	MDW_LOG_DEBUG("File ["<< theUrl <<"] found and will be returned:");
	response->clear();
	
	file >> std::noskipws;
	std::copy(  std::istream_iterator<char>(file), 
				std::istream_iterator<char>(), 
				std::back_inserter(*response.get()));	

    return true;
}


