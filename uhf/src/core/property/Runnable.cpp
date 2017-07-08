#include "uhf/core/property/Runnable.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IRunnable.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;
using namespace uhf::component;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::property::Runnable)

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

	void Runnable::readPtree(const ptree::Node& ptree)
	{
	  PtreeProperty::readPtree(ptree);
	}
}
}
}
