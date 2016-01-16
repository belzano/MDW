#include "Configuration.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

void* onLibInit()
{
  toolbox::Maker::instance().registration<uhf::core::configuration::Bootstrap>();
  toolbox::Maker::instance().registration<uhf::core::configuration::ComponentInstance>();
  toolbox::Maker::instance().registration<uhf::core::configuration::ComponentConfiguration>();
  toolbox::Maker::instance().registration<uhf::core::configuration::PropertyInstance>();
  toolbox::Maker::instance().registration<uhf::core::configuration::PropertyConfiguration>();
  
  toolbox::ptree::helper::RegisterPtreeClassPtr<uhf::core::configuration::Bootstrap>();
  toolbox::ptree::helper::RegisterPtreeClassPtr<uhf::core::configuration::ComponentInstance>();
  toolbox::ptree::helper::RegisterPtreeClassPtr<uhf::core::configuration::ComponentConfiguration>();
  toolbox::ptree::helper::RegisterPtreeClassPtr<uhf::core::configuration::PropertyInstance>();
  toolbox::ptree::helper::RegisterPtreeClassPtr<uhf::core::configuration::PropertyConfiguration>();

  toolbox::ptree::helper::RegisterPtreeClass<uhf::core::configuration::Bootstrap>();
  toolbox::ptree::helper::RegisterPtreeClass<uhf::core::configuration::ComponentInstance>();
  toolbox::ptree::helper::RegisterPtreeClass<uhf::core::configuration::ComponentConfiguration>();
  toolbox::ptree::helper::RegisterPtreeClass<uhf::core::configuration::PropertyInstance>();
  toolbox::ptree::helper::RegisterPtreeClass<uhf::core::configuration::PropertyConfiguration>();

  toolbox::ptree::RegisterBridgePtreeAttribute<uhf::core::configuration::Bootstrap, U32>("version", BRIDGE_MAKE_ATTRIBUTE_ACESSORS(uhf::core::configuration::Bootstrap, getVersion()));
  toolbox::ptree::RegisterBridgePtreeAttribute<uhf::core::configuration::Bootstrap, std::list<uhf::core::configuration::ComponentInstancePtr>>("components", BRIDGE_MAKE_ATTRIBUTE_ACESSORS(uhf::core::configuration::Bootstrap, getComponents()));  

  return 0;
}
void* init = onLibInit();

//////////////////////////////////////////////////////////////////////////////////////
    
namespace uhf{
namespace core{
namespace configuration{

  void Bootstrap::readPtree(const toolbox::ptree::ptree& ptree)
  {
      toolbox::bridge::bridge(ptree, *this);
      
      MDW_LOG_DEBUG("Loaded bootstrap with version " << m_version);
  }

  //////////////////////////////////////////////////////////////////////////////////////
    
  void ComponentInstance::readPtree(const toolbox::ptree::ptree& )
  {
    
  }
    
  //////////////////////////////////////////////////////////////////////////////////////
    
  void PropertyInstance::readPtree(const toolbox::ptree::ptree& )
  {
    
  }
    
  //////////////////////////////////////////////////////////////////////////////////////
    
}
}
}