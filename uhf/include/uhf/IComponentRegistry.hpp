#pragma once

#include "uhf/IComponent.hpp"
#include <list>


namespace uhf {

/////////////////////////////////////////////////////////////////////

	class IComponentRegistry : public IComponent
	{
		friend class IComponent;
		
	public:
		IComponentRegistry();
		virtual ~IComponentRegistry();

		virtual void getComponents(std::list<IComponentPtr>& components) const = 0;
		
		template<class ComponentT>
		void registerComponent(std::shared_ptr<ComponentT> component) { 
			registerComponent(std::dynamic_pointer_cast<IComponent>(component));
		}
		/*
		template<class ComponentT>
		std::shared_ptr<ComponentT> getComponent() { 
			IComponentPtr ptr = getComponentInstance(IComponent::getTypename<ComponentT>());
			return std::dynamic_pointer_cast<ComponentT>(ptr);
		}*/
		
		virtual std::ostream& toStream(std::ostream& stream) const;
		
	protected:
		virtual IComponentPtr getComponent(const ComponentTypeName& componentName) = 0;
		
		virtual void registerComponent(IComponentPtr component) = 0;
	};
	
	typedef std::shared_ptr<IComponentRegistry> IComponentRegistryPtr;

///////////////////////////////////////////////////////////////////////////////////////

}

std::ostream& operator<<(std::ostream& iStream, const uhf::IComponentRegistry& iEntity);

