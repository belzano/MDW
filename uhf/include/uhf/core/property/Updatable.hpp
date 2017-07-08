#pragma once

#include "toolbox/Types.hpp"
#include "uhf/core/property/PtreeProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {	
namespace core {
namespace property {

	class UpdateEventArgs
	{
		
	};
	 
	//////////////////////////////////////////////////////////////////////////////////////
	
	class Updatable: public PtreeProperty
	{
	public:
		virtual bool checkConsistency(uhf::IComponentPtr componentInstance) const override;
		
		virtual void readPtree(const toolbox::ptree::Node&) override;

		virtual std::ostream& toStream(std::ostream& stream) const override;	
    };	

	typedef std::shared_ptr<Updatable> UpdatablePtr;

}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::property::Updatable)
