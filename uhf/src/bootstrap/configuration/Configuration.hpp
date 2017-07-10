#pragma once

#include "toolbox/Types.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"
#include "uhf/IComponentConfiguration.hpp"

#include "PtreeProperty.hpp"

#include <list>

namespace uhf {
namespace bootstrap {
namespace configuration {

    //////////////////////////////////////////////////////////////////////////////////////
    
    class ComponentConfiguration: public uhf::IComponentConfiguration, public toolbox::ptree::PtreeEntity
    {
	public:
	  ComponentConfiguration(){}
	  
	  virtual void readPtree(const toolbox::ptree::Node&) override;
	  virtual void writePtree(toolbox::ptree::Node& ) const override {}
	  
	  virtual std::ostream& toStream(std::ostream& stream) const override { return stream;}
    };
    
    MDW_SHARED_POINTER(ComponentConfiguration)
        
    //////////////////////////////////////////////////////////////////////////////////////
    
    class ComponentInstance: public toolbox::ptree::PtreeEntity
    {
	public:
		ComponentInstance(){}

		virtual void readPtree(const toolbox::ptree::Node&) override;
		virtual void writePtree(toolbox::ptree::Node& ) const override {}

		virtual std::ostream& toStream(std::ostream& stream) const override;

		std::string& 		getTypename() 	   {return m_typename;}
		std::string const& 	getTypename() const {return m_typename;}

		std::list<uhf::bootstrap::property::PtreePropertyPtr>& 		getProperties() 	  {return m_properties;}
		std::list<uhf::bootstrap::property::PtreePropertyPtr> const& getProperties() const {return m_properties;}

		ComponentConfigurationPtr & 	 getConfiguration()  		{return m_configuration;}
		ComponentConfigurationPtr const& getConfiguration() const   {return m_configuration;}

		std::string 		 								m_typename;
		std::list<uhf::bootstrap::property::PtreePropertyPtr> 	m_properties;
		ComponentConfigurationPtr 							m_configuration;
    };
    
    MDW_SHARED_POINTER(ComponentInstance)
  
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
		
		std::list< std::string>& 	getLibraries()       {return m_libraries;}
		std::list< std::string> const& getLibraries() const {return m_libraries;}
		
		std::list< ComponentInstancePtr>& 	getComponents()       {return m_components;}
		std::list< ComponentInstancePtr> const& getComponents() const {return m_components;}
		
		U32 m_version;
		std::list<std::string> 			 m_libraries;
		std::list< ComponentInstancePtr> m_components;
    };
    
    MDW_SHARED_POINTER(Bootstrap)
  
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::configuration::Bootstrap)
MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::configuration::ComponentInstance)
MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::configuration::ComponentConfiguration)

    
