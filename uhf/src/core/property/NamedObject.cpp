

#include "uhf/core/property/NamedObject.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Helper.hpp"

////////////////////////////////////////////////////////////

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
	 
	std::ostream& NamedObject::toStream(std::ostream& stream) const 
	{
	  stream << "Name: " << m_name << " "; 
	  return stream;
	}

}
}
}
