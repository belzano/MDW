#include "EventManager.hpp"

namespace logger
{
	////////////////////////////////////////

	EventManager& EventManager::Instance()
	{
		static EventManager manager;
		return manager;
	}

}
