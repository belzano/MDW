
#include "toolbox/Logger.hpp"
#include "toolbox/entity/Factory.hpp"

#include "uhf/core/ComponentMakerRegistry.hpp"

#include "service/ServiceDiskInfo.hpp"
#include "service/ServiceProcInfo.hpp"
#include "service/ServiceSystemInfo.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInitUhfSysmon()
{
  MDW_LOG_INFO("libuhfsysmon.so: ctor");

  //toolbox::entity::Factory::instance().registration<uhf::core::configuration::Bootstrap>();

  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::sysmon::component::ServiceDiskInfo>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::sysmon::component::ServiceSystemInfo>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::sysmon::component::ServiceProcInfo>();
  
  return 0;
}
void* initUhfSysmon = onLibInitUhfSysmon();

//////////////////////////////////////////////////////////////////////////////////////
