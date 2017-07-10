#include "Activable.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IActivable.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;
using namespace uhf::component;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::bootstrap::property::Activable)

namespace uhf {	
namespace bootstrap {
namespace property {
	
	//////////////////////////////////////////////////////////////////////////////////////

	void Activable::readPtree(const ptree::Node& ptree)
	{
	  PtreeProperty::readPtree(ptree);
	}
}
}
}
