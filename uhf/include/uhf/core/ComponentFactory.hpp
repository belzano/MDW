#pragma once

#include "uhf/IComponent.hpp"


namespace uhf {
namespace core {

/////////////////////////////////////////////////////////////////////

class ComponentFactory
{
    public:     
        // singleton 
		static ComponentFactory& instance();
				
		template <class T>
		std::shared_ptr<T> make()
		{
			uhf::ComponentTypeName componentName = uhf::IComponent::getTypename<T>();
			return make<T>(componentName);
		}

		template <class T>
		std::shared_ptr<T> make(uhf::ComponentTypeName componentName)
		{
			uhf::IComponentPtr ptr = make(componentName);
			return std::dynamic_pointer_cast<T>(ptr);
		}

		uhf::IComponentPtr make(uhf::ComponentTypeName const& key);

    private:
		ComponentFactory(){}
		ComponentFactory(const ComponentFactory&);
		  
		
};

///////////////////////////////////////////////////////////////////////////////////////


}
}
