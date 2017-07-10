#pragma once

#include "uhf/core/property/Updatable.hpp"
#include "PtreeProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/Types.hpp"
#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {	
namespace bootstrap {
namespace property {
	 
	//////////////////////////////////////////////////////////////////////////////////////
	
	class Updatable: public PtreeProperty, public uhf::core::property::Updatable
	{
	public:
		virtual void readPtree(const toolbox::ptree::Node&) override;
		
		virtual bool equals(IPropertyPtr other) const override;

		virtual std::ostream& toStream(std::ostream& stream) const override;	
    };	

	typedef std::shared_ptr<Updatable> UpdatablePtr;

}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::bootstrap::property::Updatable)
