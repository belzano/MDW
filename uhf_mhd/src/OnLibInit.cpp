
#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"

#include "uhf/core/ComponentMakerRegistry.hpp"

#include "uhf/mhd/component/TrafficHandler.hpp"
#include "TrafficHandlerConfiguration.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInitUhfMhd()
{
  MDW_LOG_INFO("libuhfmhd.so: ctor")
	
  //toolbox::entity::Factory::instance().registration<uhf::mhd::component::TrafficHandler>();
  toolbox::entity::Factory::instance().registration<uhf::http::TrafficHandlerConfiguration>();
  
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::mhd::component::TrafficHandler>();
  
  return 0;
}

void* initUhfUhf = onLibInitUhfMhd();
