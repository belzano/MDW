#include "uhf/IComponent.hpp"
#include "uhf/IBroker.hpp"

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
void IComponent::setBroker(IBrokerPtr broker)
{
	m_broker = broker;
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
