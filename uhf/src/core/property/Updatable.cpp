

#include "uhf/core/property/Updatable.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace uhf::component;
using namespace toolbox;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::property::Updatable)

namespace uhf {	
namespace core {
namespace property {
	
	bool Updatable::checkConsistency(uhf::IComponentPtr componentInstance) const
	{ 
		// check the instance is an updatable
		uhf::component::IUpdatablePtr upcastedInstance = std::dynamic_pointer_cast<uhf::component::IUpdatable>(componentInstance);
		return upcastedInstance != nullptr;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////
	
	bool Updatable::equals(IPropertyPtr other) const 
	{
		UpdatablePtr otherUpdatable = std::dynamic_pointer_cast<Updatable>(other);
		return otherUpdatable != nullptr;
	}

	//////////////////////////////////////////////////////////////////////////////////////

	void Updatable::readPtree(const ptree::Node& ptree)
	{
	  PtreeProperty::readPtree(ptree);
	}
	 
	std::ostream& Updatable::toStream(std::ostream& stream) const 
	{
	  PtreeProperty::toStream(stream);
	  return stream;
	}

}
}
}
