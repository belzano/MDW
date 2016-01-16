#include "HttpTrafficHandler.hpp"
#include "HttpConnection.hpp"

#include "platform.h"
#include <iostream>
#include <string>

#include <signal.h>
#include <pthread.h>

#include <microhttpd.h>

#include "uhf/http/InvocationRequest.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#include "StaticPages.hpp"

/////////////////////////////////////////////////////////////////////

static int 
accept_connection(MHD_Connection* connection, 
                const char* url, 
				const char* method, 
				void** ioConCtx)
{
    MDW_LOG_DEBUG("  Creating new transaction\n");	
    
	//if (concurrent_cnx_count >= MAXCLIENTS)
	//	return send_reponse (connection, busypage, MHD_HTTP_SERVICE_UNAVAILABLE);

	HttpConnection *con_info = new HttpConnection(connection);
	if (nullptr == con_info)
		return MHD_NO;
		
	if (! con_info->accept(url, method))
	{
		MDW_LOG_WARNING("Connection request for ["<< url <<"/"<< method << "] denied.");
		return MHD_NO;
	}
		
	// Store context to dedicated placeholder
	*ioConCtx = (void *) con_info;
	return MHD_YES;	
}
 
/////////////////////////////////////////////////////////////////////

static int
send_reponse (struct MHD_Connection *connection, const char *page, int status_code)
{
    MDW_LOG_DEBUG("send_reponse");	
	
	struct MHD_Response *response = MHD_create_response_from_data(strlen (page), (void *) page, 0 /*must_free*/, 0 /*must_copy*/);   			     
	if (!response)
		return MHD_NO;

	int ret = MHD_queue_response (connection, status_code, response);
	MHD_destroy_response (response);

	return ret;
}

/////////////////////////////////////////////////////////////////////

static void
on_response_sent (	void */*cls*/, 
					struct MHD_Connection */*connection*/,
					void **ioConCtx, 
					enum MHD_RequestTerminationCode)
{
    MDW_LOG_DEBUG ("on_response_sent");	
	
	HttpConnection* con_info = (HttpConnection*) *ioConCtx;
	if (NULL == con_info)
		return;

	con_info->onResponseSent();

	delete con_info;
	*ioConCtx = NULL;
}

/////////////////////////////////////////////////////////////////////

static int
on_data_reception (void * /*cls*/, 
					  struct MHD_Connection* connection,
                      const char* url, 
                      const char* method,
                      const char* /*version*/, 
                      const char* upload_data,
                      size_t* upload_data_size, 
                      void** ioConCtx)
{
    MDW_LOG_DEBUG ("on_data_reception");	
		
	// No context: New incoming cnx		
	if (NULL == *ioConCtx)
    {
		return accept_connection(connection, url, method, ioConCtx);
    }

	HttpConnection *con_info = (HttpConnection*) *ioConCtx;
	if (nullptr == con_info)
		return send_reponse (connection, StaticPages::ClientError, MHD_HTTP_BAD_REQUEST);
	
	return con_info->onDataReceived(upload_data, upload_data_size);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

namespace uhf
{
		
	HttpTrafficHandler::HttpTrafficHandler(int port)
		: _port(port)
	{}

	////////////////////////////////////////////////////////////	

	int HttpTrafficHandler::activate()
	{		
		/*
		int daemon_opts = MHD_USE_SELECT_INTERNALLY
						| MHD_USE_DEBUG 
						| MHD_USE_POLL
						| MHD_USE_THREAD_PER_CONNECTION;
		*/
		if (daemon != 0)
		{
			MDW_LOG_INFO("HttpTrafficHandler is already activated!")
			return 0;
		}
		
		daemon = (void*) MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, _port, NULL, NULL,
									&on_data_reception, NULL,
									MHD_OPTION_NOTIFY_COMPLETED, 
									on_response_sent,
									NULL, MHD_OPTION_END);					
						   
		if (daemon == nullptr)
		{
			MDW_LOG_ERROR("HttpTrafficHandler returned 0");
			return 0;
		}
	
	
		MDW_LOG_INFO("HttpTrafficHandler started OK");			
		return 0;
	}
		
	////////////////////////////////////////////////////////////	

	int HttpTrafficHandler::deactivate()
	{
		if (daemon == 0)
		{
			MDW_LOG_ERROR("HttpTrafficHandler does not seem activated.");
			return 0;
		}	
		
		MHD_stop_daemon ( (struct MHD_Daemon*) daemon);
		daemon = 0;
		return 0;		
	}

	////////////////////////////////////////////////////////////	

}

////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////	
