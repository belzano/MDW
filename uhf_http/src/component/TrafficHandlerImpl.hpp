#pragma once 

#include "platform.h"
#include <microhttpd.h>

/////////////////////////////////////////////////////////////////////

/*static*/ int accept_connection(MHD_Connection* connection, 
                const char* url, 
				const char* method, 
				void** ioConCtx);
				
/*static*/ int send_reponse (struct MHD_Connection *connection, const char *page, int status_code);

/*static*/ void on_response_sent (	void */*cls*/, 
					struct MHD_Connection */*connection*/,
					void **ioConCtx, 
					enum MHD_RequestTerminationCode);
					
/*static*/ int on_data_reception (void * /*cls*/, 
					  struct MHD_Connection* connection,
                      const char* url, 
                      const char* method,
                      const char* /*version*/, 
                      const char* upload_data,
                      size_t* upload_data_size, 
                      void** ioConCtx);
