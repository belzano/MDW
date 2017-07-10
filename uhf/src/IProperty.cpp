#include "uhf/IProperty.hpp"
#include "uhf/IComponent.hpp"

////////////////////////////////////////////////////////////

namespace uhf {

//---------------------------------------------------------
IProperty::IProperty()
{
}

//---------------------------------------------------------
IProperty::~IProperty()
{
}

//---------------------------------------------------------
std::ostream& IProperty::toStream(std::ostream& stream) const 	
{
	return stream;
}
				
//---------------------------------------------------------
		
}
