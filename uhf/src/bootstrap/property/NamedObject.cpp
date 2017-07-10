
#include "NamedObject.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::bootstrap::property::NamedObject)

using namespace toolbox;

namespace uhf {	
namespace bootstrap {
namespace property {
	
	//////////////////////////////////////////////////////////////////////////////////////

	void NamedObject::readPtree(const ptree::Node& ptree)
	{
	  PtreeProperty::readPtree(ptree);
	  
	  toolbox::ptree::bridge("name", ptree, m_name);
	}
	 
	//////////////////////////////////////////////////////////////////////////////////////

	std::ostream& NamedObject::toStream(std::ostream& stream) const 
	{
	  PtreeProperty::toStream(stream);
	  uhf::core::property::NamedObject::toStream(stream);
	  return stream;
	}

}
}
}
