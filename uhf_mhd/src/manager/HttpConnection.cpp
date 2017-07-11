#include "HttpConnection.hpp"

#include "platform.h"
#include <iostream>
#include <string>
#include <microhttpd.h>

#include "StaticPages.hpp"
#include "uhf/http/InvocationRequest.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"

#define POSTBUFFERSIZE  1024

/////////////////////////////////////////////////////////////////////

static int iterate_get (void * coninfo_cls, enum MHD_ValueKind , const char *key, const char *value)
{
	MDW_LOG_DEBUG("iterate_get");
		
	HttpConnection *con_info = (HttpConnection *)coninfo_cls;

	printf ("%s: %s\n", key, value);

	std::string theKey(key);
	std::string data;
	if (NULL!= value)
		data = std::string(value, value + strlen(value));
	
	con_info->m_request._url_args.insert( { theKey, data} );
	
	return MHD_YES;
}

/////////////////////////////////////////////////////////////////////

static int iterate_post (void *coninfo_cls, enum MHD_ValueKind /*kind*/, 
				const char *key, const char *filename,
				const char */*content_type*/,
				const char */*transfer_encoding*/,
				const char *data, 
				uint64_t offset, 
				size_t size)              
{
    MDW_LOG_DEBUG("iterate_post")
	
	HttpConnection *con_info = (HttpConnection *)coninfo_cls;

	if (size <= 0)
	{
		MDW_LOG_DEBUG("  no data: skipping ")
		return MHD_YES;
	}
	
	if (key == NULL)
	{
		MDW_LOG_DEBUG("  no key: skipping ")
		return MHD_YES;
	}
	
	// TODO good we dont care but filename is surely per key
	if (filename != NULL)
		con_info->m_request._post_filename = filename;
		
	std::string theKey(key);
	con_info->m_request.setParsedData(theKey, data, size, offset);

	con_info->m_request.answerstring = toolbox::MakeDataPtr(StaticPages::Completed);
	con_info->m_request.answercode = uhf::http::StatusCode::OK;
    
    MDW_LOG_DEBUG("  iterate_post : OK");	
	
	return MHD_YES;
}

/////////////////////////////////////////////////////////////////////

HttpConnection::HttpConnection(MHD_Connection* conn)
		: m_chrono("HttpConnection path length")
		, m_request("#UNDEF#")
		, m_connection(conn)
		, m_postprocessor(NULL)
{
}

/////////////////////////////////////////////////////////////////////

HttpConnection::~HttpConnection()
{
	if (NULL != m_postprocessor)
	{
		MHD_destroy_post_processor(m_postprocessor);
	}
}

/////////////////////////////////////////////////////////////////////

bool HttpConnection::accept(const char* url, const char* method)
{	
	// Call UrlResolver to get the service associated to URL
	std::string serviceName = "TODO-UrlResolver";

	// TODO m_request should only instantiated here, once service type was resolved
	// and we re sure to accept request

	if (0 == strcmp (method, "POST"))
	{
		m_postprocessor = MHD_create_post_processor (m_connection, POSTBUFFERSIZE, iterate_post, (void *)this);
		if (NULL == m_postprocessor)
		{
			return false;
		}
		
		m_request._url = url;
		m_request.connectiontype = uhf::http::RequestType::POST;
		m_request.answercode = uhf::http::StatusCode::OK;
		
		m_request.answerstring = toolbox::MakeDataPtr(StaticPages::Completed);
	}
	else if (0 == strcmp (method, "GET"))
	{
		MHD_get_connection_values(m_connection, MHD_GET_ARGUMENT_KIND, iterate_get, (void*)this);
		
		m_request._url = url;		
		m_request.connectiontype = uhf::http::RequestType::GET;
		m_request.answercode = uhf::http::StatusCode::OK;
	}
	else
	{
		MDW_LOG_WARNING("verb ["<< method << "] not supported: Denying connexion.");
		// Other HTTP verbs are not supported!
		return false;
	}		
	
	return true;
}

/////////////////////////////////////////////////////////////////////

int HttpConnection::onDataReceived(const char* upload_data, size_t* upload_data_size)
{				
	switch (m_request.connectiontype)
	{
		case uhf::http::RequestType::POST:
			if (0 != *upload_data_size)
			{	
				MDW_LOG_DEBUG("  Processing POST data : size =" << *upload_data_size );
				m_request.pushRawData(upload_data, *upload_data_size);	
				MHD_post_process (m_postprocessor, upload_data, *upload_data_size);
				*upload_data_size = 0;

				return MHD_YES;
			}
			break;
		case uhf::http::RequestType::GET:
			break;
		default:	
			return sendResponse(StaticPages::ClientError, uhf::http::StatusCode::BAD_REQUEST);
	}
	
	m_request.answercode = uhf::http::StatusCode::OK;
	m_request.answerstring = toolbox::MakeDataPtr("GET reply");
		
	return onDataReceptionCompleted(); 	
}

/////////////////////////////////////////////////////////////////////

int HttpConnection::onDataReceptionCompleted()
{
	MDW_LOG_DEBUG( "Service invocation for url [" << m_request._url << "]");

	// TODO get a component with has a property Processor<HttpRequest>
	// Check this component has a property HttpAcceptor sa/ property->accept(url)
	
	m_request.answerstring = toolbox::MakeDataPtr("Service lookup logic is not implemented yet. Come and see in HttpConnection::onDataReceptionCompleted()  \n");
	
	//static uhf::ServiceInvocator invocator;
	//invocator.invoke(iTrx->m_request, iTrx->m_request);

	MDW_LOG_DEBUG( "Processing query for url [" << m_request._url << "]");

	std::string reply( 	m_request.answerstring->begin(),
						m_request.answerstring->end());
	// send response
   
    //memory management options for buffer; 
	// MHD_RESPMEM_PERSISTENT if the buffer is static/global memory, 
	// MHD_RESPMEM_MUST_FREE if the buffer is heap-allocated and should be freed by MHD 
	// MHD_RESPMEM_MUST_COPY if the buffer is in transient memory (i.e. on the stack) and must be copied by MHD;
	struct MHD_Response *response = 
		MHD_create_response_from_buffer (m_request.answerstring->size(), 
										 (void *) m_request.answerstring->data(),
										  MHD_RESPMEM_PERSISTENT);   		
	
	if (!response)
		return MHD_NO;

	int ret = MHD_queue_response (m_connection, m_request.answercode, response);
	MHD_destroy_response (response);

	return ret;
}

/////////////////////////////////////////////////////////////////////

int HttpConnection::sendResponse(const char *page, int status_code)
{
	// send response
   
    //memory management options for buffer; 
	// MHD_RESPMEM_PERSISTENT if the buffer is static/global memory, 
	// MHD_RESPMEM_MUST_FREE if the buffer is heap-allocated and should be freed by MHD 
	// MHD_RESPMEM_MUST_COPY if the buffer is in transient memory (i.e. on the stack) and must be copied by MHD;
	struct MHD_Response *response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_PERSISTENT);   	
				     
	if (!response)
		return MHD_NO;

	int ret = MHD_queue_response (m_connection, status_code, response);
	MHD_destroy_response (response);

	return ret;
}

/////////////////////////////////////////////////////////////////////

void HttpConnection::onResponseSent()
{
	
}
	
