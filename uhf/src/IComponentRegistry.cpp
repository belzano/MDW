#include "uhf/IComponentRegistry.hpp"


////////////////////////////////////////////////////////////

namespace uhf {	

	//---------------------------------------------------------
	IComponentRegistry::IComponentRegistry()
	{
	}

	//---------------------------------------------------------
	IComponentRegistry::~IComponentRegistry()
	{
	}

	//---------------------------------------------------------

	std::ostream& IComponentRegistry::toStream(std::ostream& stream) const 
	{
		std::list<IComponentPtr> components;
		getComponents(components);
		stream << "IComponentRegistry :" << components.size() << " registered.";
		return stream;
	}

}

////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& iStream, const uhf::IComponentRegistry& iEntity)
{ 
	return iEntity.toStream(iStream); 
}
