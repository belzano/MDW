#pragma once

#include "uhf/IComponent.hpp"
#include <list>


namespace uhf {

/////////////////////////////////////////////////////////////////////

	class IComponentRegistry
	{
	public:
		IComponentRegistry();
		virtual ~IComponentRegistry();

		virtual void getComponents(std::list<IComponentPtr>& components) = 0;
		
		template<class ComponentT>
		void registerComponent(std::shared_ptr<ComponentT> component) { 
			registerComponentInstance(component->getTypename(), std::dynamic_pointer_cast<IComponent>(component));
		}
		
		template<class ComponentT>
		std::shared_ptr<ComponentT> getComponentInstance() { 
			IComponentPtr ptr = getComponentInstance(IComponent::getTypename<ComponentT>());
			return std::dynamic_pointer_cast<ComponentT>(ptr);
		}
		
	protected:
		virtual IComponentPtr getComponentInstance(const ComponentTypeName& componentName) = 0;
		
		virtual void registerComponentInstance(const ComponentTypeName&, IComponentPtr component) = 0;
			

	};
	
	typedef std::shared_ptr<IComponentRegistry> IComponentRegistryPtr;

///////////////////////////////////////////////////////////////////////////////////////


}
