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
		
		std::list< ComponentPtr>& 	getComponents()       {return m_components;}
		std::list< ComponentPtr> const& getComponents() const {return m_components;}
		
		U32 m_version;
		std::list< ComponentPtr> m_components;
    };
    
    MDW_SHARED_POINTER(BootstrapConfiguration)
  
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::configuration::BootstrapConfiguration)
