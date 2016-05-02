

#include "gtest/gtest.h"

#include "toolbox/Types.hpp"
#include "PtreeBridge.hpp"
#include "toolbox/ptree/Helper.hpp"
#include "toolbox/StringUtils.hpp"


#define MAKE_ATTRIBUTE(attrtype, attrname)						\
const attrtype& get##attrname() const { return _##attrname; }	\
	  attrtype& get##attrname()       { return _##attrname; }	\
attrtype _##attrname;


class Document
{
public: 
	Document()
	{
		static bool registered = false;
		if (registered)
			return;
			
		toolbox::ptree::RegisterBridgePtreeAttribute<Document, std::string>("string", BRIDGE_MAKE_ATTRIBUTE_ACESSORS(Document, getString()));
		toolbox::ptree::RegisterBridgePtreeAttribute<Document, U32>("U32",BRIDGE_MAKE_ATTRIBUTE_ACESSORS(Document, getU32()));
		toolbox::ptree::RegisterBridgePtreeAttribute<Document, S32>("S32",BRIDGE_MAKE_ATTRIBUTE_ACESSORS(Document, getS32()));	
		registered = true;
	}

	MAKE_ATTRIBUTE(std::string, String)
	MAKE_ATTRIBUTE(S32, S32)
	MAKE_ATTRIBUTE(U32, U32)
};


TEST(BridgePtreeAttribute, TestReadSimpleValues)
{
	Document doc;
	toolbox::DataPtr json = toolbox::MakeDataPtr("{\"string\":\"prout\",\"U32\":21,\"S32\":-21}");
	boost::property_tree::ptree node;
	toolbox::ptree::helper::ReadPtree(json, node);
	
	toolbox::bridge::bridge(node, doc);
	
	EXPECT_EQ("prout", doc._String);
	EXPECT_EQ(21u, doc._U32);
	EXPECT_EQ(-21, doc._S32);
}

TEST(BridgePtreeAttribute, TestWriteSimpleValues)
{
	Document doc;
	doc._String = "prout";
	doc._U32 = 21;
	doc._S32 = -21;
	
	boost::property_tree::ptree node;
	toolbox::bridge::bridge(doc, node);
	
	toolbox::DataPtr json(new toolbox::Data());	
	toolbox::ptree::helper::WritePtree(node, json);
	
	
	std::string jsonAsString(json->data(), json->size());
	toolbox::eraseAllChars(jsonAsString, " \n");
	
	EXPECT_EQ("{\"string\":\"prout\",\"U32\":\"21\",\"S32\":\"-21\"}", jsonAsString);
}





class StlDocument
{
public:
	StlDocument()
	{
		static bool registered = false;
		if (registered)
			return;
			
		toolbox::ptree::RegisterBridgePtreeAttribute<StlDocument, std::list<U32>>("ListU32",BRIDGE_MAKE_ATTRIBUTE_ACESSORS(StlDocument, getListU32()));
		registered = true;
	}
	 
	MAKE_ATTRIBUTE(std::list<U32>, ListU32)
};


TEST(BridgePtreeAttribute, TestReadStlContainers)
{
	StlDocument doc;
	
	toolbox::DataPtr json = toolbox::MakeDataPtr("{\"ListU32\": [10,21]}");
	boost::property_tree::ptree node;
	toolbox::ptree::helper::ReadPtree(json, node);
	
	toolbox::bridge::bridge(node, doc);
	
	EXPECT_EQ(2u, doc._ListU32.size());
	EXPECT_EQ(10u, doc._ListU32.front());
	EXPECT_EQ(21u, doc._ListU32.back());
}

TEST(BridgePtreeAttribute, TestWriteStlContainers)
{
	StlDocument doc;
	doc._ListU32.push_back(10);
	doc._ListU32.push_back(21);
	
	boost::property_tree::ptree node;
	toolbox::bridge::bridge(doc, node);
	
	toolbox::DataPtr json(new toolbox::Data());	
	toolbox::ptree::helper::WritePtree(node, json);
	
	std::string jsonAsString(json->data(), json->size());
	toolbox::eraseAllChars(jsonAsString, " \n");

	EXPECT_EQ("{\"ListU32\":[\"10\",\"21\"]}", jsonAsString);
}

/*
TEST_F(BridgePtreeAttributeBasic, DefaultValues)
{
	Document doc; 
	doc._String = "dummy";
	doc._U32    = 42;
	doc._S32    = 42;
	
	toolbox::DataPtr json = toolbox::MakeDataPtr("{}");
	boost::property_tree::ptree node;
	toolbox::ptree::helper::ReadPtree(json, node);
	
	toolbox::bridge::bridge<boost::property_tree::ptree, Document>(node, doc);
	
	EXPECT_EQ("", doc._String);
	EXPECT_EQ(0u, doc._U32);
	EXPECT_EQ(0 , doc._S32);
}*/


class ChildDocument
{
public: 
	ChildDocument()
	{
		static bool registered = false;
		if (registered)
			return;
			
		toolbox::ptree::RegisterBridgePtreeAttribute<ChildDocument, std::string>("string", BRIDGE_MAKE_ATTRIBUTE_ACESSORS(ChildDocument, getString()));
		registered = true;
	}

	MAKE_ATTRIBUTE(std::string, String)
};


class RootDocument
{
public: 
	RootDocument()
	{
		static bool registered = false;
		if (registered)
			return;
			
		toolbox::ptree::RegisterBridgePtreeAttribute<RootDocument, ChildDocument>("ChildDocument", BRIDGE_MAKE_ATTRIBUTE_ACESSORS(RootDocument, getChildDocument()));
		registered = true;
	}

	MAKE_ATTRIBUTE(ChildDocument, ChildDocument)
};


TEST(BridgePtreeAttribute, TestReadPodContainer)
{
	RootDocument doc;
	toolbox::DataPtr json = toolbox::MakeDataPtr("{\"ChildDocument\": { \"string\":\"prout\"} }");
	boost::property_tree::ptree node;
	toolbox::ptree::helper::ReadPtree(json, node);
	
	toolbox::bridge::bridge(node, doc);
	
	EXPECT_EQ("prout", doc._ChildDocument._String);
}

TEST(BridgePtreeAttribute, TestWritePodContainer)
{
	RootDocument doc;
	doc._ChildDocument._String = "prout";
	
	boost::property_tree::ptree node;
	toolbox::bridge::bridge(doc, node);
	
	toolbox::DataPtr json(new toolbox::Data());	
	toolbox::ptree::helper::WritePtree(node, json);
	
	
	std::string jsonAsString(json->data(), json->size());
	toolbox::eraseAllChars(jsonAsString, " \n");
	
	EXPECT_EQ("{\"ChildDocument\":{\"string\":\"prout\"}}", jsonAsString);
}

