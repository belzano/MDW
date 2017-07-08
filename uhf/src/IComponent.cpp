#include "uhf/IComponent.hpp"
#include "uhf/IComponentRegistry.hpp"
#include "toolbox/Logger.hpp"

////////////////////////////////////////////////////////////

namespace uhf {	

	//---------------------------------------------------------
	IComponent::IComponent()
		: m_isInitialized(false)
	{
	}

	//---------------------------------------------------------
	IComponent::~IComponent()
	{
	}

	/////////////////////////////////////////////////////////////////////////////////

	bool IComponent::initialize(IComponentPtr iThis,
								IComponentRegistryPtr componentRegistry, 
								std::list<IPropertyPtr> properties,
								IComponentConfigurationPtr iConfiguration)
	{
		if (iThis.get() != this) {
			MDW_LOG_ERROR("Invalid pointer to self provided.");
			return false;
			//throw new Exception("Component intialization shoud provide a shared pointer to this.");
		}
		
		// Check this component is not already initialized / registered
		
		// Check properties are consistent with this instance
		for (auto prop: properties) {
			if (! prop->checkConsistency(iThis)) {
				MDW_LOG_ERROR("Property check failed." << iThis->getTypename() << "/" << prop->getTypename());
				return false;
			}
		}
		
		m_componentRegistry = componentRegistry;
		m_properties = properties;
		m_configuration = iConfiguration;
		
		onInitialize();
				
		m_isInitialized = true;
				
		componentRegistry->registerComponent(iThis);
		
		return true;
	}

	/////////////////////////////////////////////////////////////////////////////////

	bool IComponent::hasProperty(const std::string& iTypeName)	
	{ 
		return getProperty(iTypeName) != nullptr;
	}

	/////////////////////////////////////////////////////////////////////////////////

	IPropertyPtr IComponent::getProperty(const std::string& iTypeName)
	{ 
		for(auto prop : m_properties)
		{
			// TOD handle inheritance if (prop->isA(iTypeName))
			if (iTypeName == prop->getTypename())
				return prop;
		}
		return IPropertyPtr();
	}

}
