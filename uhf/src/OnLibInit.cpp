
#include "BootstrapConfiguration.hpp"
#include "Configuration.hpp"

#include "uhf/core/ComponentMakerRegistry.hpp"

#include "uhf/core/component/Bootstrap.hpp"
#include "uhf/core/component/Runner.hpp"
#include "kvs/component/LocalMemory.hpp"
#include "kvs/component/FileSystem.hpp"
#include "kvs/component/EnvVar.hpp"
#include "logger/component/Console.hpp"
#include "http/component/ServiceGetFile.hpp"

#include "uhf/core/property/Runnable.hpp"
#include "uhf/core/property/Updatable.hpp"
#include "uhf/core/property/Activable.hpp"
#include "uhf/core/property/NamedObject.hpp"

#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInitUhfCore()
{
  MDW_LOG_INFO("libuhfcore.so: ctor")
  
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::Bootstrap>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::BootstrapConfiguration>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::ComponentInstance>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::ComponentConfiguration>();
  
  toolbox::entity::Factory::instance().registration<uhf::core::property::Runnable>();
  toolbox::entity::Factory::instance().registration<uhf::core::property::Updatable>();
  toolbox::entity::Factory::instance().registration<uhf::core::property::Activable>();
  toolbox::entity::Factory::instance().registration<uhf::core::property::NamedObject>();
  
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::Bootstrap>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::Runner>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::kvs::component::LocalMemory>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::kvs::component::FileSystem>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::kvs::component::EnvVar>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::logger::component::Console>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::http::component::ServiceGetFile>();
  
  return 0;
}
void* initUhfCore = onLibInitUhfCore();

//////////////////////////////////////////////////////////////////////////////////////
