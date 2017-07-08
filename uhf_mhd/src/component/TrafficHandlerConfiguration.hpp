#pragma once

#include "toolbox/Types.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

#include "uhf/IComponentConfiguration.hpp"

namespace uhf {
namespace http {
    
    //////////////////////////////////////////////////////////////////////////////////////
    
    class TrafficHandlerConfiguration: public uhf::IComponentConfiguration, public toolbox::ptree::PtreeEntity
    {
	public:
	  TrafficHandlerConfiguration(){}

	  virtual void readPtree(const toolbox::ptree::Node&) override;
	  virtual void writePtree(toolbox::ptree::Node& ) const override {}
	  
	  virtual std::ostream& toStream(std::ostream& stream) const override;
	  
	  U32 m_port;
    };
    
    MDW_SHARED_POINTER(TrafficHandlerConfiguration)
    
    //////////////////////////////////////////////////////////////////////////////////////
        
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::http::TrafficHandlerConfiguration)

    
