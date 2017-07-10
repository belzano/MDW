#include "uhf/core/property/Runnable.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IRunnable.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;
using namespace uhf::component;

namespace uhf {	
namespace core {
namespace property {
	
	bool Runnable::checkConsistency(IComponentPtr componentInstance) const
	{ 
		// check the instance is a Runnable
		IRunnablePtr upcastedInstance = std::dynamic_pointer_cast<IRunnable>(componentInstance);
		return upcastedInstance != nullptr;
	}
		
	//////////////////////////////////////////////////////////////////////////////////////

	bool Runnable::equals(IPropertyPtr other) const 
	{
		RunnablePtr otherRunnable = std::dynamic_pointer_cast<Runnable>(other);
		return otherRunnable != nullptr;
	}
	
}
}
}
