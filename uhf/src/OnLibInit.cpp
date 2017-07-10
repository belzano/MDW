
#include "BootstrapConfiguration.hpp"
#include "Configuration.hpp"

#include "uhf/core/ComponentMakerRegistry.hpp"

#include "uhf/core/component/Runner.hpp"
#include "uhf/core/component/Updater.hpp"
#include "uhf/core/component/UpdateSleeper.hpp"
#include "uhf/core/component/Sleeper.hpp"
#include "uhf/bootstrap/component/Bootstrap.hpp"
#include "kvs/component/LocalMemory.hpp"
#include "kvs/component/FileSystem.hpp"
#include "kvs/component/EnvVar.hpp"
#include "logger/component/Console.hpp"
#include "http/component/ServiceGetFile.hpp"

#include "Runnable.hpp"
#include "Updatable.hpp"
#include "Activable.hpp"
#include "NamedObject.hpp"

#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInitUhfCore()
{
  MDW_LOG_INFO("libuhfcore.so: ctor")
  
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::configuration::Bootstrap>();
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::configuration::BootstrapConfiguration>();
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::configuration::ComponentInstance>();
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::configuration::ComponentConfiguration>();
  
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::property::Runnable>();
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::property::Updatable>();
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::property::Activable>();
  toolbox::entity::Factory::instance().registration<uhf::bootstrap::property::NamedObject>();
  
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::Bootstrap>();  
  
  
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::Runner>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::Updater>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::UpdateSleeper>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::Sleeper>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::kvs::component::LocalMemory>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::kvs::component::FileSystem>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::kvs::component::EnvVar>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::logger::component::Console>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::http::component::ServiceGetFile>();
  
  return 0;
}
void* initUhfCore = onLibInitUhfCore();

//////////////////////////////////////////////////////////////////////////////////////
