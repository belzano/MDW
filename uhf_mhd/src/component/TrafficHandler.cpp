#include "TrafficHandler.hpp"
#include "TrafficHandlerImpl.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

namespace uhf {
namespace http {
		
	TrafficHandler::TrafficHandler()
		: IComponent()
		, _port(888)
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

	int TrafficHandler::activate()
	{		
		/*
		int daemon_opts = MHD_USE_SELECT_INTERNALLY
						| MHD_USE_DEBUG 
						| MHD_USE_POLL
						| MHD_USE_THREAD_PER_CONNECTION;
		*/
		if (m_impl != nullptr)
		{
			MDW_LOG_INFO("HttpTrafficHandler is already activated!")
			return 0;
		}
		
		m_impl = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, _port, NULL, NULL,
									&on_data_reception, NULL,
									MHD_OPTION_NOTIFY_COMPLETED, 
									on_response_sent,
									NULL, MHD_OPTION_END);					
						   
		if (m_impl == nullptr)
		{
			MDW_LOG_ERROR("HttpTrafficHandler returned 0");
			return 0;
		}
	
	
		MDW_LOG_INFO("HttpTrafficHandler started OK");			
		return 0;
	}
		
	////////////////////////////////////////////////////////////	

	int TrafficHandler::deactivate()
	{
		if (m_impl == nullptr)
		{
			MDW_LOG_ERROR("HttpTrafficHandler does not seem activated.");
			return 0;
		}	
		
		MHD_stop_daemon (m_impl);
		m_impl = nullptr;
		return 0;		
	}

	////////////////////////////////////////////////////////////	

}
}



////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////	
