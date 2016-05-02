

#include "gtest/gtest.h"

#include "toolbox/Types.hpp"
#include "PtreeBridge.hpp"
#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"
#include "toolbox/StringUtils.hpp"


#define MAKE_ATTRIBUTE(attrtype, attrname)						\
const attrtype& get##attrname() const { return _##attrname; }	\
	  attrtype& get##attrname()       { return _##attrname; }	\
attrtype _##attrname;



class Component : public toolbox::ptree::PtreeEntity
{
public: 
    static constexpr const char* TypeName = "Component";
    Component()
    {
	static bool registered = false;
	if (registered)
	    return;

	toolbox::ptree::RegisterBridgePtreeAttribute<Component, std::string>("string", BRIDGE_MAKE_ATTRIBUTE_ACESSORS(Component, getString()));
	registered = true;
    }

    virtual void readPtree(const toolbox::ptree::Node& ptree)
    {
	toolbox::bridge::bridge(ptree, *this);
    }
    virtual void writePtree(toolbox::ptree::Node& ){}
    
    MAKE_ATTRIBUTE(std::string, String)
    
    virtual std::string GetType(){ return TypeName; }
};


class ComponentImpl: public Component
{
public: 
    static constexpr const char* TypeName = "ComponentImpl";
    ComponentImpl()
    {
	static bool registered = false;
	if (registered)
	    return;

	registered = true;
    }
    
    virtual void readPtree(const boost::property_tree::ptree& ptree)
    {
	Component::readPtree(ptree);
	toolbox::bridge::bridge(ptree, *this);
    }
    void writePtree(toolbox::ptree::Node& ){}

    virtual std::string GetType(){ return TypeName; }
};


TEST(BridgePtreeClass, TestReadClass)
{
    toolbox::bridge::BridgeClass<boost::property_tree::ptree, std::shared_ptr<Component> >::Instance() = 
	new toolbox::ptree::BridgePtreeClassPtr<Component>();
  
    toolbox::entity::Factory::instance().registration<Component>();
    toolbox::entity::Factory::instance().registration<ComponentImpl>();

    std::shared_ptr<Component> cmp = std::shared_ptr<Component>(nullptr);
    toolbox::DataPtr json = toolbox::MakeDataPtr("{\"$type\":\"ComponentImpl\",\"string\":\"prout\",\"U32\":21,\"S32\":-21}");
    boost::property_tree::ptree node;
    toolbox::ptree::helper::ReadPtree(json, node);
    
    toolbox::bridge::bridge(node, cmp);
    
    EXPECT_NE(nullptr, cmp.get());
    EXPECT_EQ("prout", cmp->_String);
    EXPECT_EQ("ComponentImpl", cmp->GetType());
}
