#include "Updater.hpp"

#include "UpdaterThread.hpp"
#include "Thread.hpp"
#include "ThreadManager.hpp"

#include "uhf/core/aspects/IUpdatable.hpp"
#include "uhf/IComponentRegistry.hpp"

namespace uhf {
namespace manager {

/////////////////////////////////////////////////////////////////////

void Updater::start(uhf::component::IUpdatablePtr iUpdatable)
{
	ThreadPtr thread( new UpdaterThread("Thread uhf::manager::Updater", iUpdatable));
	_manager.registerThread(thread);
	_manager.activate();
}

/////////////////////////////////////////////////////////////////////

void Updater::stop()
{
	_manager.deactivate();
}

}
}


