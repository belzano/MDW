#include "toolbox/ptree/Conversions.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/Base64.hpp"

#include <cstring>

////////////////////////////////////////////////////////////////////

#define MME_PARSE_INTEGER_TYPE(type)			\
void convert(const Node& iNode, type& oResult) \
{ oResult = atoi(iNode.data().c_str()); } 		\
void convert(const type& iData, Node& oNode) 	\
{ oNode.data() = toolbox::ToString(iData); }

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

void convert(const Node& iNode, std::string& oResult)
{
	oResult = iNode.data();
}

void convert(const std::string& iData, Node& oNode)
{
	oNode.data() = iData;
}

//////////////////////////////////////////////////////////

void convert(const Node& iData, Node& oNode)
{
	oNode = iData;
}

//////////////////////////////////////////////////////////

void convert(const Node& iNode, toolbox::DataPtr& oBinaryData)
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

void convert(const toolbox::DataPtr& iBinaryData, Node& oNode)
{
	// Handle no data case
	if (iBinaryData.get() == nullptr)
		return;
		
	toolbox::DataPtr theAsciiData = toolbox::base64::base64(iBinaryData);
	std::copy(theAsciiData->begin(), theAsciiData->end(), back_inserter( oNode.data() ));
}

//////////////////////////////////////////////////////////

void convert(const toolbox::ptree::PtreeEntity& iEntity, Node& oNode)
{
	iEntity.writePtree(oNode);
}
	
void convert(const Node& iNode, toolbox::ptree::PtreeEntity& oEntity)
{
	oEntity.readPtree(iNode);
}

//////////////////////////////////////////////////////////
// containers of string

MDW_PTREE_CONVERSION_OBJECT_DEFINE(U32)
MDW_PTREE_CONVERSION_OBJECT_DEFINE(S32)
MDW_PTREE_CONVERSION_OBJECT_DEFINE(std::string)
MDW_PTREE_CONVERSION_OBJECT_DEFINE(Node)

MDW_PTREE_CONVERSION_ENTITY_DEFINE(toolbox::ptree::PtreeEntity)

