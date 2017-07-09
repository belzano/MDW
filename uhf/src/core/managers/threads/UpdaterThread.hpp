#pragma once

#include "toolbox/Types.hpp"
#include "uhf/core/aspects/IUpdatable.hpp"
#include "Thread.hpp"

namespace uhf{
namespace manager{	
	
	class UpdaterThread : public Thread
	{
		public:	
			UpdaterThread(const std::string& name, 
						uhf::component::IUpdatablePtr );
						
			virtual void run() override;
			
		private:
			uhf::component::IUpdatablePtr _updatable;
	};

}
}
