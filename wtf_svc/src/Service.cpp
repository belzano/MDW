#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdint.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Service.hpp"

using namespace WTF;

using std::vector;
using boost::property_tree::ptree;
using std::make_pair;




Service::Service()	
{

}

///////////////////////////////////////////////////////////////

Service::Service(const char* )	
{

}

///////////////////////////////////////////////////////////////


bool Service::preprocess() 
{
	return true;
}

///////////////////////////////////////////////////////////////

bool Service::invoke(const std::string url,
					 const std::map<std::string, std::string>& urlargs, 			 
					 const std::map<std::string, toolbox::DataPtr>& postargs,
					 toolbox::DataPtr& response)
{
	try
	{
		// preInvoke
		if (! preprocess())
		{
			response = toolbox::MakeDataPtr("preInvoke failed.");
			return false;
		}	
	
		// invoke	
		if (! process(url, urlargs, postargs, response))
		{
			return false;
		}
    
		// postInvoke
		if (! postprocess())
		{
			response = toolbox::MakeDataPtr("postInvoke failed.");
			return false;
		}	
		
		return true;
	}
	catch (...)
	{
	
	}
	
	return false;
}


///////////////////////////////////////////////////////////////

bool Service::postprocess() 
{
	return true;
}

///////////////////////////////////////////////////////////////
/*
void Service::_generateOutput(void *data, outputType type, string& output)
{
    std::ostringstream ostr;
    ptree *pt = (ptree *) data;
    if (TYPE_JSON == type)
        write_json(ostr, *pt);
    else if (TYPE_XML == type)
        write_xml(ostr, *pt);

    output = ostr.str();
}*/

