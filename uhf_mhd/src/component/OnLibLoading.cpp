
#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"

#include "uhf/core/ComponentMakerRegistry.hpp"
#include "TrafficHandler.hpp"
#include "TrafficHandlerConfiguration.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInitUfhHttp()
{
  MDW_LOG_INFO("libuhfhttp.so: ctor")
	
  toolbox::entity::Factory::instance().registration<uhf::http::TrafficHandler>();
  toolbox::entity::Factory::instance().registration<uhf::http::TrafficHandlerConfiguration>();
  
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::http::TrafficHandler>();
  
  return 0;
}

void* initUhfHttp = onLibInitUfhHttp();
