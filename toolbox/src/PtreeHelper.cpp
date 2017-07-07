#include "toolbox/PtreeHelper.hpp"
#include "toolbox/StringUtils.hpp"
#include "toolbox/Base64.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <cstring>

////////////////////////////////////////////////////////////////////

#define MME_PARSE_INTEGER_TYPE(type)\
	template<> void ptreeToObject<type>(const boost::property_tree::ptree& iNode, type& oResult) { oResult = atoi(iNode.data().c_str()); } \
	template<> void objectToPtree<type>(const type& iData, boost::property_tree::ptree& oNode) { oNode.data() = toolbox::ToString(iData); }

	MME_PARSE_INTEGER_TYPE(S8)
    MME_PARSE_INTEGER_TYPE(U8)    
	MME_PARSE_INTEGER_TYPE(S16)
	MME_PARSE_INTEGER_TYPE(U16)
	MME_PARSE_INTEGER_TYPE(S32)
	MME_PARSE_INTEGER_TYPE(U32)
	MME_PARSE_INTEGER_TYPE(S64)
	MME_PARSE_INTEGER_TYPE(U64)

#undef MME_PARSE_INTEGER_TYPE

///////// /////////////////////////////////////////////////

template<>
void ptreeToObject<std::string>(const boost::property_tree::ptree& iNode, std::string& oResult)
{
	oResult = iNode.data();
}

template<>
void objectToPtree<std::string>(const std::string& iData, boost::property_tree::ptree& oNode)
{
	oNode.data() = iData;
}

//////////////////////////////////////////////////////////

template<>
void ptreeToObject<toolbox::DataPtr>(const boost::property_tree::ptree& iNode, toolbox::DataPtr& oBinaryData)
{
	// Handle no data case
	if (iNode.data().empty())
	{
		oBinaryData = toolbox::DataPtr(new toolbox::Data());
		return;
	}
	
	// Get ptree data to a DataPtr
	toolbox::DataPtr asciiData (new toolbox::Data());
	std::copy(iNode.data().begin(), iNode.data().end(), back_inserter(* asciiData.get()));
	
	oBinaryData = toolbox::base64::unbase64( asciiData );
}

template<>
void objectToPtree<toolbox::DataPtr>(const toolbox::DataPtr& iBinaryData, boost::property_tree::ptree& oNode)
{
	// Handle no data case
	if (iBinaryData.get() == nullptr)
		return;
		
	toolbox::DataPtr theAsciiData = toolbox::base64::base64(iBinaryData);
	std::copy(theAsciiData->begin(), theAsciiData->end(), back_inserter( oNode.data() ));
}

//////////////////////////////////////////////////////////
// containers of string

MME_DEFINE_PTREE_SERIALIZER_LIST(std::string) 
MME_DEFINE_PTREE_SERIALIZER_SET(std::string) 
MME_DEFINE_PTREE_SERIALIZER_VECTOR(std::string)

//////////////////////////////////////////////////////////

namespace toolbox
{	
	void PtreeDocumentBase::toJson(DataPtr oData) const 
	{
		boost::property_tree::ptree rootNode;
		toPtree(rootNode);
			
		std::stringstream ss;
		write_json(ss, rootNode);
			
		oData->assign(std::istreambuf_iterator<char>( ss ), 
					  std::istreambuf_iterator<char>() );		
	}
		
	void PtreeDocumentBase::fromJson(DataPtr iData)
	{
		toolbox::DataPtrStreamWrapper dataBuffer(iData);
		std::istream is(&dataBuffer);	
		
		boost::property_tree::ptree pt;		
		boost::property_tree::read_json(is, pt);
		toObject(pt);
	}
	
	void PtreeDocumentBase::fromJson(const std::string& filename)
	{
		boost::property_tree::ptree pt;		
		boost::property_tree::read_json(filename, pt);
		toObject(pt);
	}
				
}
