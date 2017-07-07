#include "uhf/core/component/Runner.hpp"
#include "RunnerImpl.hpp"

namespace uhf {
namespace component {
		
	/////////////////////////////////////////////////////////////////////

	Runner::Runner()
	  : IComponent()
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