#pragma once

#include "uhf/http/InvocationRequest.hpp"
#include "toolbox/Types.hpp"

#include <string>
#include <map>

namespace uhf {
namespace http {
	
	//////////////////////////////////////////////////////////
	
	class ServiceContext
	{
	public:
		std::map<std::string, std::string>& getStaticParameters() { return _staticParameters;}	
		std::map<std::string, std::string> _staticParameters;	
	};

	//////////////////////////////////////////////////////////
	
	class Service
	{   
	public:
		
		Service();
		virtual ~Service() {}
		
		int invoke(std::shared_ptr<uhf::http::InvocationRequest>);
		
	protected:	
		virtual int preprocess();
		
		virtual int process(std::shared_ptr<uhf::http::InvocationRequest>) = 0;

		virtual int postprocess();

			  ServiceContext& getContext() 		 { return m_context; }  
		const ServiceContext& getContext() const { return m_context; }   
		
	private:

		ServiceContext m_context;
		
	};


}
}  // namespace uhf
