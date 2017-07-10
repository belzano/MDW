#include "PtreeProperty.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::bootstrap::property::PtreeProperty)

namespace uhf {	
namespace bootstrap {
namespace property {
	
	//////////////////////////////////////////////////////////////////////////////////////

	void PtreeProperty::readPtree(const ptree::Node& ptree)
	{
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	}

}
}
}
