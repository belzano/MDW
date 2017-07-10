#pragma once

#include "uhf/core/property/NamedObject.hpp"
#include "PtreeProperty.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace bootstrap {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class NamedObject : public PtreeProperty, public uhf::core::property::NamedObject
    {
    public:
		virtual void readPtree(const toolbox::ptree::Node&) override;

		virtual std::ostream& toStream(std::ostream& stream) const override ;
    };
    
	typedef std::shared_ptr<NamedObject> NamedObjectPtr;

}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::property::NamedObject)
