#pragma once

#include "uhf/core/property/Runnable.hpp"
#include "PtreeProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace bootstrap {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class Runnable : public PtreeProperty, public uhf::core::property::Runnable
    {
    public:
		virtual void readPtree(const toolbox::ptree::Node&) override;	
		
    };
    
	typedef std::shared_ptr<Runnable> RunnablePtr;
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::property::Runnable)
