
#include "BootstrapConfiguration.hpp"
#include "Configuration.hpp"

#include "uhf/core/ComponentMakerRegistry.hpp"
#include "uhf/core/component/Bootstrap.hpp"
#include "kvs/component/LocalMemory.hpp"
#include "kvs/component/FileSystem.hpp"
#include "kvs/component/EnvVar.hpp"
#include "uhf/logger/component/Console.hpp"

#include "toolbox/entity/Factory.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInitUhfCore()
{
  MDW_LOG_INFO("libuhfcore.so: ctor")
  
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::Bootstrap>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::Component>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::ComponentConfiguration>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::PropertyInstance>();
  toolbox::entity::Factory::instance().registration<uhf::core::configuration::PropertyConfiguration>();
  
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::Bootstrap>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::kvs::LocalMemory>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::kvs::FileSystem>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::kvs::EnvVar>();
  uhf::core::ComponentMakerRegistry::registerComponentMaker<uhf::component::logger::Console>();
  
  return 0;
}
void* initUhfCore = onLibInitUhfCore();

//////////////////////////////////////////////////////////////////////////////////////
