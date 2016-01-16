#pragma once

#include "toolbox/Types.hpp"
#include <string>

namespace uhf {
namespace service {
	
	/*	
	class InvocationContext
	{
	public:
		std::map<std::string, std::string>& getStaticParameters() { return _staticParameters;}
		std::map<std::string, std::string> _staticParameters;	
	};
	*/
	
	//////////////////////////////////////////////////////////////

	//class Payload;
	
	//////////////////////////////////////////////////////////////
	
	class InvocationRequest
	{

	public:
		typedef std::string ServiceType;
			
		InvocationRequest(ServiceType m_type);
		virtual ~InvocationRequest();

		const ServiceType& getType() const;
			
	private:
		ServiceType m_type;
	};
	
	//////////////////////////////////////////////////////////////

}
}
