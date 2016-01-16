
#include "uhf/http/Service.hpp"
#include "uhf/http/ServiceRegistry.hpp"

#include "toolbox/utils/Registry.hpp"
#include "toolbox/utils/Factory.hpp"

#include "toolbox/Logger.hpp"

WTF_REGISTRY_INSTANCIATION(toolbox::SharedPtrFactory<uhf::http::Service>)

namespace uhf {
namespace http {

////////////////////////////////////////////////////////////////////
    
std::shared_ptr<uhf::http::Service> ServiceRegistry::getService(const std::string& svcKey)
{
	//MDW_LOG_DEBUG("looking on service ["<< svcKey << "]");	
	std::shared_ptr<toolbox::SharedPtrFactory<uhf::http::Service> > svcFactory = toolbox::SimpleRegistry< toolbox::SharedPtrFactory<Service> >::instance().get(svcKey);
	if (svcFactory.get() == nullptr)
	{	
		//MDW_LOG_DEBUG("Service not found ["<< svcKey << "]");
		return std::shared_ptr<uhf::http::Service>((uhf::http::Service*) nullptr); 
	}	
	
	//MDW_LOG_DEBUG("Service found ["<< svcKey << "]");
	return svcFactory->newInstance();
}

////////////////////////////////////////////////////////////////////

}
}
