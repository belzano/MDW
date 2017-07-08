#include "uhf/core/component/Runner.hpp"
#include "toolbox/Logger.hpp"
#include "RunnerImpl.hpp"

namespace uhf {
namespace component {
		
	/////////////////////////////////////////////////////////////////////

	Runner::Runner()
	  :IComponent(),
	   IActivable()
	  , m_impl(new RunnerImpl())
	{
		
	}
		
	/////////////////////////////////////////////////////////////////////

	Runner::~Runner()
	{
		delete m_impl;
	}
	
	/////////////////////////////////////////////////////////////////////

	void Runner::onActivate()
	{
		MDW_LOG_INFO("Runner activation")
		m_impl->asyncStart();
	}			
	
	/////////////////////////////////////////////////////////////////////

	void Runner::onPassivate()
	{
		MDW_LOG_INFO("Runner passivation")
		m_impl->asyncStop();
	}	
}
}
