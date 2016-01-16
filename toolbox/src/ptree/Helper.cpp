#include "toolbox/ptree/Helper.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/Base64.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <cstring>

//////////////////////////////////////////////////////////

namespace toolbox {
namespace ptree {
namespace helper {
	
	void WritePtree(const boost::property_tree::ptree& iNode, toolbox::DataPtr oData)
	{			
		std::stringstream ss;
		write_json(ss, iNode);
			
		oData->assign(std::istreambuf_iterator<char>( ss ), 
					  std::istreambuf_iterator<char>() );		
	}

	////////////////////////////////////////////////////////////////////
	void ReadPtree(toolbox::DataPtr iData, boost::property_tree::ptree& oNode)
	{
		toolbox::DataPtrStreamWrapper dataBuffer(iData);
		std::istream is(&dataBuffer);	
		
		boost::property_tree::read_json(is, oNode);
	}

	////////////////////////////////////////////////////////////////////
	void ReadPtree(const std::string& filename, boost::property_tree::ptree& oNode)
	{
		boost::property_tree::read_json(filename, oNode);
	}

}
}
}