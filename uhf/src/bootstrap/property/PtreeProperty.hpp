#pragma once

#include "uhf/IProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace bootstrap {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class PtreeProperty : public toolbox::ptree::PtreeEntity
    {
    public:
		virtual void readPtree(const toolbox::ptree::Node&);
		virtual void writePtree(toolbox::ptree::Node& ) const override {}

		virtual std::ostream& toStream(std::ostream& stream) const override { 
			return toolbox::ptree::PtreeEntity::toStream(stream);
		}		
    };
    
	typedef std::shared_ptr<PtreeProperty> PtreePropertyPtr;
}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::property::PtreeProperty)
