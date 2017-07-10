

#include "Updatable.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace uhf::component;
using namespace toolbox;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::bootstrap::property::Updatable)

namespace uhf {	
namespace bootstrap {
namespace property {
	
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
	 
	//////////////////////////////////////////////////////////////////////////////////////

	std::ostream& Updatable::toStream(std::ostream& stream) const 
	{
	  PtreeProperty::toStream(stream);
	  uhf::core::property::Updatable::toStream(stream);
	  return stream;
	}

}
}
}
