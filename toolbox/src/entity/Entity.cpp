#include "toolbox/entity/Entity.hpp"

std::ostream& operator<<(std::ostream& iStream, const toolbox::entity::Entity& iEntity)
{ 
	return iEntity.toStream(iStream); 
}
