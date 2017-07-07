#include "TrafficHandlerImpl.hpp"

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

int accept_connection(MHD_Connection* connection, 
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

int send_reponse (struct MHD_Connection *connection, const char *page, int status_code)
{
    MDW_LOG_DEBUG("send_reponse");	
	
	//struct MHD_Response *response = MHD_create_response_from_data(strlen (page), (void *) page, 0 /*must_free*/, 0 /*must_copy*/);   			     
	
	//memory management options for buffer; 
	// MHD_RESPMEM_PERSISTENT if the buffer is static/global memory, 
	// MHD_RESPMEM_MUST_FREE if the buffer is heap-allocated and should be freed by MHD 
	// MHD_RESPMEM_MUST_COPY if the buffer is in transient memory (i.e. on the stack) and must be copied by MHD;
	struct MHD_Response *response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_PERSISTENT);   			     
	if (!response)
		return MHD_NO;

	int ret = MHD_queue_response (connection, status_code, response);
	MHD_destroy_response (response);

	return ret;
}

/////////////////////////////////////////////////////////////////////

void on_response_sent (	void */*cls*/, 
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

int on_data_reception (void * /*cls*/, 
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
