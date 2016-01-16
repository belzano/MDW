#include "uhf/core/component/Runner.hpp"
#include "RunnerImpl.hpp"

namespace uhf {
namespace core {
namespace component {
		
	/////////////////////////////////////////////////////////////////////

	Runner::Runner(IBrokerPtr broker)
	  : IComponent(broker)
	  , m_impl(new RunnerImpl())
	{
		
	}
		
	/////////////////////////////////////////////////////////////////////

	Runner::~Runner()
	{
		delete m_impl;
	}
	
	/////////////////////////////////////////////////////////////////////

	int Runner::run()
	{
		return m_impl->run();
	}			
}
}
}
