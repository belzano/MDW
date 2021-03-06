

#include "uhf/core/property/Updatable.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace uhf::component;
using namespace toolbox;

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
	
	std::ostream& Updatable::toStream(std::ostream& stream) const 
	{
		return stream;
	}

}
}
}
