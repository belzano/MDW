#pragma once

#include "uhf/service/InvocationRequest.hpp"
#include "toolbox/Types.hpp"
#include "uhf/http/RequestType.hpp"
#include "uhf/http/StatusCode.hpp"

namespace uhf {
namespace http {
	
	class InvocationRequest : public uhf::service::InvocationRequest
	{

	public:		
		InvocationRequest(const char* serviceName);
		virtual ~InvocationRequest();
		
		const std::string& getHttpServiceName()const { return m_serviceName; }
		
		void setParsedData( const std::string& iKey, const char *data, size_t size, uint64_t offset);
		void pushRawData( const char *data, size_t size);
	
		RequestType connectiontype;
		
		std::string _url;
		std::map<std::string, std::string>  _url_args;
		 
		std::string _post_filename;
		
		std::shared_ptr< std::vector<char> > _raw_post_data;
		std::map< std::string, std::shared_ptr< std::vector<char> > > _parsed_post_data;
		
		std::shared_ptr< std::vector<char> >  answerstring;
		StatusCode answercode;
	private:
		std::string m_serviceName;
		
	};
	
	//////////////////////////////////////////////////////////////
}
}
