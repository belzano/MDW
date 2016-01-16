#pragma once

#include <iostream>
#include <string>
#include "wtf/http/Service.hpp"
#include "wtf/http/ServiceFactory.hpp"
#include "wtf/http/ServiceRegistry.hpp"

namespace WTF
{

template <class T>
struct ServiceName
{
	static std::string Name();
};

//////////////////////////////////////////////////////////////////////

template<class ServiceT>
void registerServiceFactoryTemplate()
{
	std::string serviceName ( ServiceName<ServiceT>::Name() );
	ServiceRegistry::instance().registerService(
		serviceName, 
		std::shared_ptr<ServiceFactory>((ServiceFactory*) new ServiceFactoryTemplate<ServiceT>() )
	);
}

//////////////////////////////////////////////////////////////////////

#define WTF_SERVICE_REGISTRATION( ServiceP )\
namespace WTF\
{\
	template<>\
	struct ServiceName< ServiceP >\
	{\
		static std::string Name() { return std::string("" #ServiceP "" );}\
	};\
}\
void (*loader##ServiceP)(void) __attribute__ ((section (".ctors"))) \
			= WTF::registerServiceFactoryTemplate<ServiceP>;

//////////////////////////////////////////////////////////////////////

template <class ServiceT>
class ServiceTemplate : public Service
{
public:
  
	ServiceTemplate() : Service() {}
       
    virtual bool process(const std::string url,
						 const std::map<std::string, std::string>& urlargs, 			 
						 const std::map<std::string, toolbox::DataPtr>& postargs,
						 toolbox::DataPtr& response) = 0;   
   
private:
    
};

}

