#pragma once

#include "uhf/core/property/PtreeProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace core {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class Activable : public PtreeProperty
    {
    public:
		virtual bool checkConsistency(IComponentPtr componentInstance) const override;
		
		virtual void readPtree(const toolbox::ptree::Node&) override;	
    };
    
	typedef std::shared_ptr<Activable> ActivablePtr;
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::property::Activable)
