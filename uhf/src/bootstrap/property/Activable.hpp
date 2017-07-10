#pragma once

#include "uhf/core/property/Activable.hpp"
#include "PtreeProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace bootstrap {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class Activable : public PtreeProperty, public uhf::core::property::Activable
    {
    public:
		virtual void readPtree(const toolbox::ptree::Node&) override;	
    };
    
	typedef std::shared_ptr<Activable> ActivablePtr;
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::property::Activable)
