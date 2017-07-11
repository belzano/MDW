#include "uhf/mhd/component/TrafficHandler.hpp"
#include "TrafficHandlerImpl.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

namespace uhf {
namespace mhd {
namespace component {
		
	TrafficHandler::TrafficHandler()
		: IComponent()
		, m_impl(nullptr)
		, _port(8888)
	{}

	////////////////////////////////////////////////////////////	
		
	TrafficHandler::~TrafficHandler()
	{
		if (m_impl != nullptr)
		{
			MDW_LOG_ERROR("Dirty shutdown! TrafficHandler is still active.")
		}
	}

	////////////////////////////////////////////////////////////	

	void TrafficHandler::onActivate()
	{		
		/*
		int daemon_opts = MHD_USE_SELECT_INTERNALLY
						| MHD_USE_DEBUG 
						| MHD_USE_POLL
						| MHD_USE_THREAD_PER_CONNECTION;
		*/
		if (m_impl != nullptr)
		{
			MDW_LOG_WARNING("HttpTrafficHandler is already activated!")
			return;
		}
		
		m_impl = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, _port, NULL, NULL,
									&on_data_reception, NULL,
									MHD_OPTION_NOTIFY_COMPLETED, 
									on_response_sent,
									NULL, MHD_OPTION_END);					
						   
		if (m_impl == nullptr)
		{
			MDW_LOG_ERROR("MHD_start_daemon failed to initialize. Check the provided port number "
			 << _port <<" is free and does not require root privileges (<1024)");
			return;
		}
	
		MDW_LOG_INFO("HttpTrafficHandler started OK on port " << _port);			
	}
		
	////////////////////////////////////////////////////////////	

	void TrafficHandler::onPassivate()
	{
		if (m_impl == nullptr)
		{
			MDW_LOG_ERROR("HttpTrafficHandler does not seem activated.");
			return;
		}	
		
		MHD_stop_daemon (m_impl);
		m_impl = nullptr;
	}

	////////////////////////////////////////////////////////////	

}
}
}



////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////	
