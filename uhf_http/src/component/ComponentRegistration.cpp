
#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"

#include "TrafficHandler.hpp"
#include "TrafficHandlerConfiguration.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInit()
{
  MDW_LOG_INFO("libuhfhttp.so: ctor")
	
  toolbox::entity::Factory::instance().registration<uhf::http::TrafficHandler>();
  toolbox::entity::Factory::instance().registration<uhf::http::TrafficHandlerConfiguration>();
  return 0;
}

void* init = onLibInit();
