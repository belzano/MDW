

#include "uhf/core/property/NamedObject.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::property::NamedObject)

using namespace toolbox;

namespace uhf {	
namespace core {
namespace property {
	
	//////////////////////////////////////////////////////////////////////////////////////

	bool NamedObject::equals(IPropertyPtr other) const 
	{
		NamedObjectPtr otherNamedObject = std::dynamic_pointer_cast<NamedObject>(other);
		return otherNamedObject != nullptr;
	}

	//////////////////////////////////////////////////////////////////////////////////////

	void NamedObject::readPtree(const ptree::Node& ptree)
	{
	  PtreeProperty::readPtree(ptree);
	  
	  toolbox::ptree::bridge("name", ptree, m_name);
	}
	 
	std::ostream& NamedObject::toStream(std::ostream& stream) const 
	{
	  PtreeProperty::toStream(stream);
	  stream << "NamedObject: " << m_name << " "; 
	  return stream;
	}

}
}
}
