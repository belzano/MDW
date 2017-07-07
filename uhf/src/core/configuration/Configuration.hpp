#pragma once

#include "toolbox/Types.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

#include <list>

namespace uhf {
namespace core {
namespace configuration {
      
    //////////////////////////////////////////////////////////////////////////////////////
    
    class PropertyConfiguration: public toolbox::ptree::PtreeEntity
    {
	public:
	  PropertyConfiguration(){}

	  virtual void readPtree(const toolbox::ptree::Node&) override;
	  virtual void writePtree(toolbox::ptree::Node& ) const override {}
	  
	  virtual std::ostream& toStream(std::ostream& stream) const override { return stream;}
    };
    
    MDW_SHARED_POINTER(PropertyConfiguration)
    
    //////////////////////////////////////////////////////////////////////////////////////
        
    class PropertyInstance: public toolbox::ptree::PtreeEntity
    {
	public:
	  PropertyInstance(){}
	  
	  virtual void readPtree(const toolbox::ptree::Node&) override;
	  virtual void writePtree(toolbox::ptree::Node& ) const override {}
	  
	  virtual std::ostream& toStream(std::ostream& stream) const override { return stream;}
	  
 	  std::string  m_propertyType;
	  std::shared_ptr<PropertyConfiguration> m_configuration;
    };
    
    MDW_SHARED_POINTER(PropertyInstance)

    //////////////////////////////////////////////////////////////////////////////////////
    
    class ComponentConfiguration: public toolbox::ptree::PtreeEntity
    {
	public:
	  ComponentConfiguration(){}
	  
	  virtual void readPtree(const toolbox::ptree::Node&) override;
	  virtual void writePtree(toolbox::ptree::Node& ) const override {}
	  
	  virtual std::ostream& toStream(std::ostream& stream) const override { return stream;}
    };
    
    MDW_SHARED_POINTER(ComponentConfiguration)
        
    //////////////////////////////////////////////////////////////////////////////////////
    
    class Component: public toolbox::ptree::PtreeEntity
    {
	public:
		Component(){}

		virtual void readPtree(const toolbox::ptree::Node&) override;
		virtual void writePtree(toolbox::ptree::Node& ) const override {}

		virtual std::ostream& toStream(std::ostream& stream) const override;

		std::string 		 			m_type;
		std::string 		 			m_name;
		std::list<std::shared_ptr<PropertyInstance>> 	m_properties;
		std::list<std::string> 			m_libraries;
		std::shared_ptr<ComponentConfiguration> 	m_configuration;
    };
    
    MDW_SHARED_POINTER(Component)
  
    //////////////////////////////////////////////////////////////////////////////////////
    
    class Bootstrap: public toolbox::ptree::PtreeEntity
    {
    public:	
		Bootstrap(){}
		
		virtual void readPtree(const toolbox::ptree::Node&) override;
		virtual void writePtree(toolbox::ptree::Node& ) const override {}
	  
		virtual std::ostream& toStream(std::ostream& stream) const override;
		  
		U32& 		getVersion() 	   {return m_version;}
		U32 const& 	getVersion() const {return m_version;}
		
		std::list< ComponentPtr>& 	getComponents()       {return m_components;}
		std::list< ComponentPtr> const& getComponents() const {return m_components;}
		
		U32 m_version;
		std::list< ComponentPtr> m_components;
    };
    
    MDW_SHARED_POINTER(Bootstrap)
  
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::configuration::Bootstrap)
MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::configuration::Component)
MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::configuration::ComponentConfiguration)
MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::configuration::PropertyInstance)
MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::configuration::PropertyConfiguration)

    
