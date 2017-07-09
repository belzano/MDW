#pragma once

#include "uhf/IProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace core {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class PtreeProperty : public IProperty, public toolbox::ptree::PtreeEntity
    {
    public:
		virtual bool checkConsistency(IComponentPtr) const override { return true; }
		
		virtual void readPtree(const toolbox::ptree::Node&);
		virtual void writePtree(toolbox::ptree::Node& ) const override {}

		virtual std::ostream& toStream(std::ostream& stream) const override { 
			return toolbox::ptree::PtreeEntity::toStream(stream);
		}		
		virtual bool equals(IPropertyPtr other) const;
    };
    
	typedef std::shared_ptr<PtreeProperty> PtreePropertyPtr;
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::property::PtreeProperty)
