

#include "toolbox/Logger.hpp"

#include "service/ServiceCreateJob.hpp"
#include "service/ServiceGetJob.hpp"

#include "uhf/core/ComponentMakerRegistry.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInitMmeUhfCore()
{
  MDW_LOG_INFO("libmmeuhf.so: ctor")
  
  // toolbox::entity::Factory::instance().registration<uhf::core::configuration::PropertyConfiguration>();
  
  uhf::core::ComponentMakerRegistry::registerComponentMaker<mme::ServiceGetJob>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<mme::ServiceCreateJob>();
  
  return 0;
}

void* initMmeUhf = onLibInitMmeUhfCore();

//////////////////////////////////////////////////////////////////////////////////////
