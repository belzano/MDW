#pragma once

#include "toolbox/Types.hpp"
#include <string>
#include <map>

using std::string;

namespace WTF
{

class ServiceContext
{
public:
	std::map<std::string, std::string>& getStaticParameters() { return _staticParameters;}
	
	std::map<std::string, std::string> _staticParameters;
	
};


class Service
{   
public:
    
    Service();
    Service(const char* serviceName);
    virtual ~Service() {}
 
    bool invoke(const std::string url,
				const std::map<std::string, std::string>& urlargs, 			 
				const std::map<std::string, toolbox::DataPtr>& postargs,
				toolbox::DataPtr& response);
	
		  ServiceContext& getContext() 		 { return m_context; }  
	const ServiceContext& getContext() const { return m_context; }   
	
protected:
    		
    virtual bool postprocess();
    
    virtual bool preprocess();
     
    virtual bool process(const std::string url,
						 const std::map<std::string, std::string>& urlargs, 			 
						 const std::map<std::string, toolbox::DataPtr>& postargs,
						 toolbox::DataPtr& response) = 0;

private:

	ServiceContext m_context;
	
};



}  // namespace WTF
