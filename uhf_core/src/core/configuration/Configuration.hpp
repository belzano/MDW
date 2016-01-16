#pragma once

#include "toolbox/Maker.hpp"
#include "toolbox/Types.hpp"
#include "toolbox/ptree/Bridge.hpp"
#include <list>

namespace uhf {
namespace core {
namespace configuration {
      

    //////////////////////////////////////////////////////////////////////////////////////
    
    class PropertyConfiguration: public toolbox::Object
    {
	public:
	  static constexpr const char* TypeName = "uhf.core.configuration.PropertyConfiguration";
	  
	  PropertyConfiguration(){}

	  void readPtree(const toolbox::ptree::ptree& ){}
	  void writePtree(toolbox::ptree::ptree& ){}
    };
    MDW_SHARED_POINTER(PropertyConfiguration)
    
    //////////////////////////////////////////////////////////////////////////////////////
        
    class PropertyInstance: public toolbox::Object
    {
	public:
	  static constexpr const char* TypeName = "uhf.core.configuration.PropertyInstance";
	  
	  PropertyInstance(){}
	  
	  void readPtree(const toolbox::ptree::ptree& );
	  void writePtree(toolbox::ptree::ptree& ){}
	  
 	  std::string  m_propertyType;
	  std::shared_ptr<PropertyConfiguration> m_configuration;
    };
    MDW_SHARED_POINTER(PropertyInstance)

    //////////////////////////////////////////////////////////////////////////////////////
    
    class ComponentConfiguration: public toolbox::Object
    {
	public:
	  static constexpr const char* TypeName = "uhf.core.configuration.ComponentConfiguration";
	  
	  ComponentConfiguration(){}
	  
	  void readPtree(const toolbox::ptree::ptree& ){}
	  void writePtree(toolbox::ptree::ptree& ){}
    };
    MDW_SHARED_POINTER(ComponentConfiguration)
        
    //////////////////////////////////////////////////////////////////////////////////////
    
    class ComponentInstance: public toolbox::Object
    {
	public:
	  static constexpr const char* TypeName = "uhf.core.configuration.ComponentInstance";
	  
	  ComponentInstance(){}
	  
	  void readPtree(const toolbox::ptree::ptree& );
	  void writePtree(toolbox::ptree::ptree& ){}
	  
 	  std::string 		 			m_type;
 	  std::list<std::shared_ptr<PropertyInstance>> 	m_properties;
 	  std::list<std::string> 			m_libraries;
	  std::shared_ptr<ComponentConfiguration> 	m_configuration;
    };
    MDW_SHARED_POINTER(ComponentInstance)
  
    //////////////////////////////////////////////////////////////////////////////////////
    
    class Bootstrap: public toolbox::Object
    {
    public:
	static constexpr const char* TypeName = "uhf.core.configuration.Bootstrap";
	
	Bootstrap(){}
	
	void readPtree(const toolbox::ptree::ptree& );
	void writePtree(toolbox::ptree::ptree& ){}
      
	U32& 		getVersion() 	   {return m_version;}
	U32 const& 	getVersion() const {return m_version;}
	
	std::list< ComponentInstancePtr>& 	getComponents()       {return m_components;}
	std::list< ComponentInstancePtr> const& getComponents() const {return m_components;}
	
	U32 m_version;
	std::list< ComponentInstancePtr> m_components;
    };
    MDW_SHARED_POINTER(Bootstrap)
  
}
}
}