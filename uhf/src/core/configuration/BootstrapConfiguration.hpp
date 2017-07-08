#pragma once

#include "toolbox/Types.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

#include "uhf/IComponentConfiguration.hpp"
#include "Configuration.hpp"

#include <list>

namespace uhf {
namespace core {
namespace configuration {
      
    //////////////////////////////////////////////////////////////////////////////////////
    
    class BootstrapConfiguration: public IComponentConfiguration, public toolbox::ptree::PtreeEntity
    {
    public:	
		BootstrapConfiguration(){} 
		
		virtual void readPtree(const toolbox::ptree::Node&) override;
		virtual void writePtree(toolbox::ptree::Node& ) const override {}
	  
		virtual std::ostream& toStream(std::ostream& stream) const override;
		  
		U32& 		getVersion() 	   {return m_version;}
		U32 const& 	getVersion() const {return m_version;}
		
		std::list< toolbox::ptree::Node>& 	getComponents()       {return m_components;}
		std::list< toolbox::ptree::Node> const& getComponents() const {return m_components;}
		
		std::list< std::string>& 	getLibraries()       {return m_libraries;}
		std::list< std::string> const& getLibraries() const {return m_libraries;}
				
		U32 m_version;
		std::list< std::string> m_libraries;
		std::list< toolbox::ptree::Node> m_components;
    };
    
    MDW_SHARED_POINTER(BootstrapConfiguration)
  
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::configuration::BootstrapConfiguration)
