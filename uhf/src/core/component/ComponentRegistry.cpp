
#include "uhf/core/component/ComponentRegistry.hpp"

#include "toolbox/Logger.hpp"


////////////////////////////////////////////////////////////

namespace uhf {
namespace component {
	
	ComponentRegistry::ComponentRegistry()
	{

	}

	//---------------------------------------------------------

	ComponentRegistry::~ComponentRegistry()
	{

	}	
		
	//---------------------------------------------------------

	void ComponentRegistry::onActivate(){
		MDW_LOG_INFO("ComponentRegistry: onActivation")
	}

	//---------------------------------------------------------

	void ComponentRegistry::onPassivate(){	
		MDW_LOG_INFO("ComponentRegistry: onPassivation")
	}
		
	//---------------------------------------------------------
	void ComponentRegistry::registerComponent(IComponentPtr instance)
	{
		m_components.push_back(instance);
	}

	//---------------------------------------------------------
	IComponentPtr ComponentRegistry::getComponent(const std::string& componentTypeName)
	{
		std::list<IComponentPtr> components;
		getComponents(components);
		for (auto find : components)
		{
			if (find->getTypename() == componentTypeName)
				return find;
		}
		return IComponentPtr(nullptr);
	}

	//---------------------------------------------------------
	void ComponentRegistry::getComponents(std::list<IComponentPtr>& components) const 
	{
		for(auto component : m_components)
			components.push_back(component);
	}

	//---------------------------------------------------------
	
	std::ostream& ComponentRegistry::toStream(std::ostream& stream) const {
		return IComponentRegistry::toStream(stream);
	}
}
}
