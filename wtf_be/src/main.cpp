#include "platform.h"
#include <iostream>
#include <string>

#include <signal.h>
#include <pthread.h>

#include <microhttpd.h>

#include "QueryReply.hpp"
#include "ServiceInvocator.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/ScopedChrono.hpp"


#define POSTBUFFERSIZE  1024
#define MAXCLIENTS      50

static unsigned int concurrent_cnx_count = 0;

//////////////////////////////////////////////////////////////////

class Transaction
{
public:
	Transaction(): _chrono("Transaction path length") {}
	
	toolbox::ScopedChrono _chrono;
	
	WTF::Query _query;
	WTF::Reply _reply;
	
	struct MHD_PostProcessor *postprocessor;
};

//////////////////////////////////////////////////////////////////

const char *completepage =
  "<html><body>The upload has been completed.</body></html>\n";

const char *errorpage =
  "<html><body>Page not found.</body></html>\n";

const char *servererrorpage =
  "<html><body>Server error. Please retry later.</body></html>\n";
 
/////////////////////////////////////////////////////////////////////

static int
send_page (struct MHD_Connection *connection, 
		   const char *page,
           int status_code)
{
    MDW_LOG_DEBUG("send_page");	
	
	struct MHD_Response *response =
			MHD_create_response_from_data(strlen (page), (void *) page,
                                          0 /*must_free*/, 0 /*must_copy*/);   			     
	if (!response)
		return MHD_NO;

	int ret = MHD_queue_response (connection, status_code, response);
	MHD_destroy_response (response);

	return ret;
}

static int
process_query_and_reply (struct MHD_Connection *connection, 
						 Transaction* iTrx)
{
	MDW_LOG_DEBUG( "Service invocation for url [" << iTrx->_query._url << "]");

	// compute query
	static WTF::ServiceInvocator invocator;
	invocator.invoke(iTrx->_query, iTrx->_reply);


	std::string reply( 	iTrx->_reply.answerstring->begin(),
						iTrx->_reply.answerstring->end());
	// send response
	struct MHD_Response *response =
			MHD_create_response_from_data(iTrx->_reply.answerstring->size(), 
										 (void *) iTrx->_reply.answerstring->data(),
                                          0 /*must_free*/, 0 /*must_copy*/);   			     
	if (!response)
		return MHD_NO;

	int ret = MHD_queue_response (connection, iTrx->_reply.answercode, response);
	MHD_destroy_response (response);

	return ret;
}


/////////////////////////////////////////////////////////////////////

static int
iterate_get (void * coninfo_cls, enum MHD_ValueKind , const char *key,
               const char *value)
{
	MDW_LOG_DEBUG("iterate_get");
		
	Transaction *con_info = (Transaction *)coninfo_cls;

	printf ("%s: %s\n", key, value);

	std::string theKey(key);
	std::string data;
	if (NULL!= value)
		data = std::string(value, value + strlen(value));
	
	con_info->_query._url_args.insert( { theKey, data});
	
	return MHD_YES;
}

/////////////////////////////////////////////////////////////////////

static int
iterate_post (  void *coninfo_cls,
				enum MHD_ValueKind /*kind*/,
				const char *key,
				const char *filename,
				const char */*content_type*/,
				const char */*transfer_encoding*/,
				const char *data, 
				uint64_t offset, 
				size_t size)              
{
    MDW_LOG_DEBUG("iterate_post")
	
	Transaction *con_info = (Transaction *)coninfo_cls;

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

	con_info->_reply.answerstring = toolbox::MakeDataPtr(servererrorpage);
	con_info->_reply.answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;

	// TODO good we dont care but filename is surely per key
	if (filename != NULL)
		con_info->_query._post_filename = filename;
		
	std::string theKey(key);
	con_info->_query.setParsedData(theKey, data, size, offset);

	con_info->_reply.answerstring = toolbox::MakeDataPtr(completepage);
	con_info->_reply.answercode = MHD_HTTP_OK;
    
    MDW_LOG_DEBUG("  iterate_post : OK");	
	
	return MHD_YES;
}

/////////////////////////////////////////////////////////////////////

static void
request_completed (	void */*cls*/, 
					struct MHD_Connection */*connection*/,
					void **con_cls, 
					enum MHD_RequestTerminationCode)
{
    MDW_LOG_DEBUG ("request_completed");	
	
	Transaction* con_info = (Transaction*) *con_cls;

	if (NULL == con_info)
		return;

	if (con_info->_query.connectiontype == POST)
    {
		if (NULL != con_info->postprocessor)
        {
			MHD_destroy_post_processor (con_info->postprocessor);
			concurrent_cnx_count--;
        }
    }

	delete con_info;
	*con_cls = NULL;
}

/////////////////////////////////////////////////////////////////////

static int
init_connection (MHD_Connection* connection, 
                const char* url, 
				const char* method, 
				void** con_cls)
{
    MDW_LOG_DEBUG("  Creating new transaction\n");	
    
	//if (concurrent_cnx_count >= MAXCLIENTS)
	//	return send_page (connection, busypage, MHD_HTTP_SERVICE_UNAVAILABLE);

	Transaction *con_info = new Transaction();
	if (NULL == con_info)
		return MHD_NO;

	con_info->_query._url = url;

	if (0 == strcmp (method, "POST"))
    {
		con_info->postprocessor =
			MHD_create_post_processor (connection, POSTBUFFERSIZE,
										iterate_post, (void *) con_info);

		if (NULL == con_info->postprocessor)
        {
			delete con_info;
			return MHD_NO;
        }

		concurrent_cnx_count++;

		con_info->_query.connectiontype = POST;
		con_info->_reply.answercode = MHD_HTTP_OK;
		con_info->_reply.answerstring = toolbox::MakeDataPtr(completepage);
    }
	else if (0 == strcmp (method, "GET"))
    {
		con_info->_query.connectiontype = GET;
		MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, iterate_get, (void*)con_info);
	}
	else
	{
		MDW_LOG_WARNING("verb ["<< method << "] not supported: Denying connexion.");	
			
		// Other HTTP verbs are not supported!
		delete con_info;
		return MHD_NO;
	}
		
	*con_cls = (void *) con_info;

	return MHD_YES;	
}

/////////////////////////////////////////////////////////////////////

static int
answer_to_connection (void * /*cls*/, 
					  struct MHD_Connection* connection,
                      const char* url, 
                      const char* method,
                      const char* /*version*/, 
                      const char* upload_data,
                      size_t* upload_data_size, 
                      void** con_cls)
{
    MDW_LOG_DEBUG ("answer_to_connection");	
		
	// New incoming cnx		
	if (NULL == *con_cls)
    {
		return init_connection(connection, url, method, con_cls);
    }

	Transaction *con_info = (Transaction*) *con_cls;
	
	if (0 == strcmp (method, "GET"))
    {
		MDW_LOG_DEBUG("  Answering to GET");
			
		con_info->_reply.answercode = MHD_HTTP_OK;
		con_info->_reply.answerstring = toolbox::MakeDataPtr("GET reply");

		return process_query_and_reply(connection, con_info);
    }

	if (0 == strcmp (method, "POST"))
    {
		Transaction *con_info = (Transaction*) *con_cls;

		if (0 != *upload_data_size)
        {	
			MDW_LOG_DEBUG("  Processing POST data : size =" << *upload_data_size );
				
			con_info->_query.pushRawData(upload_data, *upload_data_size);
				
			MHD_post_process (con_info->postprocessor, upload_data,	*upload_data_size);
			*upload_data_size = 0;

			return MHD_YES;
        }
        	
		return process_query_and_reply(connection, con_info);
    }

	return send_page (connection, errorpage, MHD_HTTP_BAD_REQUEST);
}

/////////////////////////////////////////////////////////////////////

static int shouldNotExit = 1;

void handle_term(int signo)
{
	MDW_LOG_INFO("Caught signal " << signo << ": Stopping soon.");
    shouldNotExit = 0;
}

//////////////////////////////////////////////////////////////////////

void* http(void *arg)
{
    int *port = (int *)arg;
    
    /*
	int daemon_opts = MHD_USE_SELECT_INTERNALLY
					| MHD_USE_DEBUG 
					| MHD_USE_POLL
					| MHD_USE_THREAD_PER_CONNECTION;
	*/
		
	struct MHD_Daemon *daemon;

	daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, *port, NULL, NULL,
								&answer_to_connection, NULL,
								MHD_OPTION_NOTIFY_COMPLETED, request_completed,
								NULL, MHD_OPTION_END);					
                       
    if (daemon == 0)
    {
		MDW_LOG_ERROR("Start Daemon returned 0");
        return 0;
    }
    
    MDW_LOG_INFO("Daemon started OK");
    
    while(shouldNotExit)
    {
        sleep(1);
    }
    
    MHD_stop_daemon (daemon);
    return 0;
}

////////////////////////////////////////////////////////////

int main (int argc, char *const *argv)
{

    if (argc != 2)
    {
        MDW_LOG_INFO ("Startup on PORT " << argv[0]);
        exit(1);
    }
    int port = atoi(argv[1]);
    
    // Hook sigterm
    MDW_LOG_INFO ("Hooking SIGTERM");
    signal(SIGTERM, handle_term);
    
    
    // Create thread
    pthread_t  thread;
    if ( 0 != pthread_create(&thread, 0 , http, &port))
    {
		MDW_LOG_FATAL("Daemon thread creation failed");	
        exit(1);
    }
    
    MDW_LOG_INFO("Daemon Thread creation OK. Waiting for SIGTERM...");
    pthread_join(thread, 0);
    return 0;
}
