#pragma once

#include <ostream>
#include <iostream>


namespace toolbox {
namespace entity {
 
    /////////////////////////////////////////////////////////////////////////////////
  
    class Entity
    {
    public:
		virtual ~Entity(){}
		
		virtual std::ostream& toStream(std::ostream& iStream) const { return iStream; }
    };
  
    /////////////////////////////////////////////////////////////////////////////////

}      
}

std::ostream& operator<<(std::ostream& iStream, const toolbox::entity::Entity& iEntity);
