#include "uhf/core/property/Activable.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IActivable.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;
using namespace uhf::component;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::property::Activable)

namespace uhf {	
namespace core {
namespace property {
	
	bool Activable::checkConsistency(IComponentPtr componentInstance) const
	{ 
		// check the instance is a Activable
		IActivablePtr upcastedInstance = std::dynamic_pointer_cast<IActivable>(componentInstance);
		return upcastedInstance != nullptr;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////

	void Activable::readPtree(const ptree::Node& ptree)
	{
	  PtreeProperty::readPtree(ptree);
	}
}
}
}
