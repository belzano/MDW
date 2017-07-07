
#include "uhf/http/component/Consumer.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdint.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>


using std::vector;
using boost::property_tree::ptree;
using std::make_pair;

namespace uhf {
namespace component {
namespace http {


Consumer::Consumer()	
{

}

///////////////////////////////////////////////////////////////

Consumer::~Consumer()	
{

}

///////////////////////////////////////////////////////////////


int Consumer::preprocess() 
{
	return 0;
}

///////////////////////////////////////////////////////////////

int Consumer::consume(std::shared_ptr<uhf::component::http::InvocationRequest> invocationRequest)
{
	try
	{
		// preInvoke
		if (! preprocess())
		{
			invocationRequest->answerstring = toolbox::MakeDataPtr("preInvoke failed.");
			return 0;
		}	
	
		// invoke	
		if (! process(invocationRequest))
		{
			return 0;
		}
    
		// postInvoke
		if (! postprocess())
		{
			invocationRequest->answerstring = toolbox::MakeDataPtr("postInvoke failed.");
			return 0;
		}	
		
		return 0;
	}
	catch (...)
	{
	
	}
	
	return 0;
}


///////////////////////////////////////////////////////////////

int Consumer::postprocess() 
{
	return 0;
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

}
}
}
