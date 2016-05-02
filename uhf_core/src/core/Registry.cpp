
#include "BootstrapConfiguration.hpp"
#include "Configuration.hpp"

#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInit()
{
  MDW_LOG_INFO("libuhfcore.so: ctor")
  
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::Bootstrap>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::Component>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::ComponentConfiguration>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::PropertyInstance>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::PropertyConfiguration>();
  
  return 0;
}
void* init = onLibInit();

//////////////////////////////////////////////////////////////////////////////////////
