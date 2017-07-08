#include "uhf/core/property/PtreeProperty.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::property::PtreeProperty)

namespace uhf {	
namespace core {
namespace property {
	
	//////////////////////////////////////////////////////////////////////////////////////

	void PtreeProperty::readPtree(const ptree::Node& ptree)
	{
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	}
}
}
}
