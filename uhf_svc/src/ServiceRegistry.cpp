
#include "uhf/service/Service.hpp"
#include "uhf/service/ServiceRegistry.hpp"

#include "toolbox/utils/Registry.hpp"
#include "toolbox/utils/Factory.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>

WTF_REGISTRY_INSTANCIATION(toolbox::SharedPtrFactory<uhf::service::Service>)

namespace uhf {
namespace service {

////////////////////////////////////////////////////////////////////
    
std::shared_ptr<Service> ServiceRegistry::getService(const std::string& svcKey)
{
	//MDW_LOG_DEBUG("looking on service ["<< svcKey << "]");	
	//std::shared_ptr<toolbox::SharedPtrFactory<uhf::service::Service> > svcFactory = toolbox::SimpleRegistry< toolbox::SharedPtrFactory<Service> >::instance().get(svcKey);
	//if (svcFactory.get() == nullptr)
	{	
		MDW_LOG_DEBUG("Service not found ["<< svcKey << "]");
		return std::shared_ptr<Service>((Service*) nullptr); 
	}	
	
	//MDW_LOG_DEBUG("Service found ["<< svcKey << "]");
	//return svcFactory->newInstance();
}

////////////////////////////////////////////////////////////////////

}
}
