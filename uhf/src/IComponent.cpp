#include "uhf/IComponent.hpp"
#include "uhf/IComponentRegistry.hpp"

////////////////////////////////////////////////////////////

namespace uhf {	

//---------------------------------------------------------
IComponent::IComponent()
{
}

//---------------------------------------------------------
IComponent::~IComponent()
{
}

//---------------------------------------------------------
void IComponent::setComponentRegistry(IComponentRegistryPtr componentRegistry)
{
	m_componentRegistry = componentRegistry;
}

//---------------------------------------------------------
void IComponent::initialize()
{	
	onInitialize();
}

//---------------------------------------------------------
void IComponent::onInitialize()
{
}

//---------------------------------------------------------
void IComponent::activate()
{	
	onActivate();
}

//---------------------------------------------------------
void IComponent::onActivate()
{
}

//---------------------------------------------------------
void IComponent::deactivate()
{	
	onDeactivate();
}

//---------------------------------------------------------
void IComponent::onDeactivate()
{
}

}
