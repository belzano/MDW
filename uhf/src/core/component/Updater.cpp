#include <chrono>
#include <thread>

#include "toolbox/Logger.hpp"

#include "uhf/IProperty.hpp"

#include "uhf/core/command/Selector.hpp"
#include "uhf/core/component/Updater.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/core/property/Updatable.hpp"

#include "uhf/IComponentRegistry.hpp"

namespace uhf {
namespace component {

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
	
	update(updatablesTyped);	
}

/////////////////////////////////////////////////////////////////////

void Updater::run()
{
	while (true)	
	{
		update();
				
		uint sleepTime = 100;
		std::chrono::milliseconds duration( sleepTime );
		std::this_thread::sleep_for(duration);
	}	
}

}
}


