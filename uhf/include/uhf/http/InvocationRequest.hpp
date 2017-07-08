#pragma once

#include "toolbox/Types.hpp"

namespace uhf {
namespace http {
	
	typedef std::string ServiceType;
	
	typedef enum 
	{
		GET = 1,
		POST = 2,
		PUT = 3,
		DELETE = 4	
	} 
	RequestType;
	
	//////////////////////////////////////////////////////////
	
	typedef enum 
	{
		OK = 200,
		BAD_REQUEST = 400,
		SERVER_ERROR = 500
	} 
	StatusCode;
	
	//////////////////////////////////////////////////////////
	
	typedef toolbox::DataPtr DataPtr;
	
	class InvocationRequest
	{

	public:		
		InvocationRequest(const char* serviceName);
		virtual ~InvocationRequest();
		
		const std::string& getHttpServiceName()const { return m_serviceName; }
		
		void setParsedData( const std::string& iKey, DataPtr data, uint64_t offset);
		void setParsedData( const std::string& iKey, const char *data, size_t size, uint64_t offset);
		
		void pushRawData( DataPtr data);
		void pushRawData( const char *data, size_t size);
	
		RequestType connectiontype;
		
		std::string _url;
		std::map<std::string, std::string>  _url_args;
		 
		std::string _post_filename;
		
		DataPtr _raw_post_data;
		std::map< std::string, DataPtr > _parsed_post_data;
		
		DataPtr  answerstring;
		
		StatusCode answercode;
		
		const ServiceType& getType() const;
	private:
		std::string m_serviceName;
		ServiceType m_type;
		
	};
	
	typedef std::shared_ptr<InvocationRequest> InvocationRequestPtr;
	
	//////////////////////////////////////////////////////////////
}
}
