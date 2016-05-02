#include "PtreeSpecializations.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/Base64.hpp"

#include <cstring>

namespace toolbox {
namespace bridge {

////////////////////////////////////////////////////////////////////

#define MME_PARSE_INTEGER_TYPE(type)\
	template<> void bridge<Node, type>(const Node& iNode, type& oResult) { oResult = atoi(iNode.data().c_str()); } \
	template<> void bridge<type, Node>(const type& iData, Node& oNode) { oNode.data() = toolbox::ToString(iData); }

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
void bridge<Node, std::string>(const Node& iNode, std::string& oResult)
{
	oResult = iNode.data();
}

template<>
void bridge<std::string, Node>(const std::string& iData, Node& oNode)
{
	oNode.data() = iData;
}

//////////////////////////////////////////////////////////

template<>
void bridge<Node, toolbox::DataPtr>(const Node& iNode, toolbox::DataPtr& oBinaryData)
{
	// Handle no data case
	if (iNode.data().empty())
	{
		oBinaryData = toolbox::DataPtr(new toolbox::Data());
		return;
	}
	
	// Get Node data to a DataPtr
	toolbox::DataPtr asciiData (new toolbox::Data());
	std::copy(iNode.data().begin(), iNode.data().end(), back_inserter(* asciiData.get()));
	
	oBinaryData = toolbox::base64::unbase64( asciiData );
}

template<>
void bridge<toolbox::DataPtr, Node>(const toolbox::DataPtr& iBinaryData, Node& oNode)
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

MME_DEFINE_PTREE_SERIALIZER_LIST(U32) 
MME_DEFINE_PTREE_SERIALIZER_SET(U32) 
MME_DEFINE_PTREE_SERIALIZER_VECTOR(U32)

MME_DEFINE_PTREE_SERIALIZER_LIST(S32) 
MME_DEFINE_PTREE_SERIALIZER_SET(S32) 
MME_DEFINE_PTREE_SERIALIZER_VECTOR(S32)

}
}
