#include "uhf/core/component/Updater.hpp"

#include "Updater.hpp"
#include <thread>
#include <chrono>

#include "toolbox/Logger.hpp"
#include "uhf/IProperty.hpp"

#include "uhf/core/command/Selector.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/core/property/Updatable.hpp"

#include "uhf/IComponentRegistry.hpp"

namespace uhf {
namespace component {

/////////////////////////////////////////////////////////////////////

Updater::Updater()
:m_impl(new uhf::manager::Updater)
{

}

/////////////////////////////////////////////////////////////////////

Updater::~Updater()
{
	delete m_impl;
}


/////////////////////////////////////////////////////////////////////

void Updater::onActivate()
{
	MDW_LOG_DEBUG("Updater activation");
	// TODO we should look for the shared ptr from the registry that contains this
	uhf::IComponentPtr badThis(this);
	
	IUpdatablePtr updatable = std::dynamic_pointer_cast<uhf::component::IUpdatable>(badThis);
	m_impl->start(updatable);
}

/////////////////////////////////////////////////////////////////////

void Updater::onPassivate() 
{
	m_impl->stop();
}

/////////////////////////////////////////////////////////////////////

void Updater::update(std::list<IUpdatablePtr>& updatables)
{
	for(auto updatable: updatables) {
		updatable->update();
	}
}

/////////////////////////////////////////////////////////////////////

void Updater::update()
{
	std::list<IComponentPtr> components;
	getComponentRegistry()->getComponents(components);
	
	// Filter updatables
	// TODO that want to be updated by me
	std::list<IComponentPtr> updatables;
	uhf::command::Selector().filter(uhf::core::property::UpdatablePtr(new uhf::core::property::Updatable()), 
								 components,
								 updatables);
	
	std::list<IUpdatablePtr> updatablesTyped;
	for (auto updatable : updatables )
	{
		updatablesTyped.push_back(std::dynamic_pointer_cast<IUpdatable>(updatable));
	}
	
	if (updatablesTyped.empty())
	{
		int napTime = 5000;
		MDW_LOG_WARNING("Nothing registered in my update loop... Gonna take a nap " << napTime << "ms ");
		std::this_thread::sleep_for(std::chrono::milliseconds(napTime));
	}
	
	update(updatablesTyped);	
}

}
}


