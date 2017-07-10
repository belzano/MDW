#include "uhf/core/property/Activable.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IActivable.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;
using namespace uhf::component;

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

	bool Activable::equals(IPropertyPtr other) const 
	{
		ActivablePtr otherActivable = std::dynamic_pointer_cast<Activable>(other);
		return otherActivable != nullptr;
	}

}
}
}
