#pragma once

#include <string>
#include "toolbox/ScopedChrono.hpp"
#include "uhf/http/InvocationRequest.hpp"


struct MHD_Connection;
struct MHD_PostProcessor;

class HttpConnection
{
	public:

		HttpConnection(MHD_Connection* conn);
		~HttpConnection();
		
		bool accept(const char* url, const char* method);

		int onDataReceived(const char* upload_data, size_t* upload_data_size);
		int onDataReceptionCompleted();
		
		int sendResponse(const char *page, int status_code);
		
		void onResponseSent();
		
	
		toolbox::ScopedChrono m_chrono;
		
		uhf::http::InvocationRequest 	m_request;
		struct MHD_Connection* 			m_connection;
		struct MHD_PostProcessor*   	m_postprocessor;	
};
