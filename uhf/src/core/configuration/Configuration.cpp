
#include "Configuration.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::Bootstrap)
MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::Component)
MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::ComponentConfiguration)
MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::PropertyInstance)
MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::PropertyConfiguration)

using namespace toolbox;
    
namespace uhf{
namespace core{
namespace configuration{

  void Bootstrap::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
	  toolbox::ptree::bridge("version", ptree, m_version);
      toolbox::ptree::bridge("components", ptree, m_components);
  }
  
  std::ostream& Bootstrap::toStream(std::ostream& stream) const 
  {
	  PtreeEntity::toStream(stream);
	  
	  stream << "Bootstrap version [" << m_version << "]" << std::endl;
	  for (auto comp: m_components)
		stream << comp << std::endl;
	  return stream;
  }
	
  //////////////////////////////////////////////////////////////////////////////////////
    
  void Component::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
      toolbox::ptree::bridge("type", ptree, m_type);
      toolbox::ptree::bridge("name", ptree, m_name);
      toolbox::ptree::bridge("properties", ptree, m_properties);
      toolbox::ptree::bridge("libraries", ptree, m_libraries);
      toolbox::ptree::bridge("configuration", ptree, m_configuration);
  }
     
  std::ostream& Component::toStream(std::ostream& stream) const 
  {
	  PtreeEntity::toStream(stream);
	  
	  stream << "Component [" << m_name << "] "; 
	  stream << "Type " << m_type << std::endl;
	  stream << "Configuration: " << m_configuration << std::endl;
	  
	  for (auto prop: m_properties)
		stream << prop << std::endl;
		
      for (auto lib: m_libraries)
		stream << lib << std::endl;
      
      return stream;
  }

  //////////////////////////////////////////////////////////////////////////////////////
    
  void ComponentConfiguration::readPtree(const ptree::Node& ptree)
  {
	 toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
  }
    
  //////////////////////////////////////////////////////////////////////////////////////
 
  void PropertyInstance::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);  
  }
    
  //////////////////////////////////////////////////////////////////////////////////////
    
  void PropertyConfiguration::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);	  
  }
    
}
}
}
