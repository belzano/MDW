#pragma once

#include "uhf/core/property/PtreeProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace core {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class Runnable : public PtreeProperty
    {
    public:
		virtual bool checkConsistency(IComponentPtr componentInstance) const override;
		
		virtual void readPtree(const toolbox::ptree::Node&) override;	
		
		virtual bool equals(IPropertyPtr other) const override;
    };
    
	typedef std::shared_ptr<Runnable> RunnablePtr;
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::property::Runnable)
