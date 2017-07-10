#include "Runnable.hpp"

#include "uhf/IComponent.hpp"
#include "uhf/core/aspects/IRunnable.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

using namespace toolbox;
using namespace uhf::component;

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::bootstrap::property::Runnable)

namespace uhf {	
namespace bootstrap {
namespace property {
	
	//////////////////////////////////////////////////////////////////////////////////////

	void Runnable::readPtree(const toolbox::ptree::Node& ptree)
	{
	  uhf::bootstrap::property::PtreeProperty::readPtree(ptree);
	}

}
}
}
