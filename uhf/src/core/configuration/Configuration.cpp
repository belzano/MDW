
#include "Configuration.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::Bootstrap)
MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::ComponentInstance)
MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::ComponentConfiguration)

using namespace toolbox;
    
namespace uhf{
namespace core{
namespace configuration{

  void Bootstrap::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
	  toolbox::ptree::bridge("version", ptree, m_version);
	  toolbox::ptree::bridge("libraries", ptree, m_libraries);
      toolbox::ptree::bridge("components", ptree, m_components);
  }
  
  std::ostream& Bootstrap::toStream(std::ostream& stream) const 
  {
	  PtreeEntity::toStream(stream);
	  
	  stream << "Bootstrap version [" << m_version << "]" << std::endl;
	  for (auto lib: m_libraries)
		stream << lib << std::endl;
	for (auto comp: m_components)
		stream << comp << std::endl;
	  return stream;
  }
	
  //////////////////////////////////////////////////////////////////////////////////////
    
  void ComponentInstance::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
      toolbox::ptree::bridge("typename", ptree, m_typename);
      toolbox::ptree::bridge("properties", ptree, m_properties);
      toolbox::ptree::bridge("configuration", ptree, m_configuration);
  }
     
  std::ostream& ComponentInstance::toStream(std::ostream& stream) const 
  {
	  PtreeEntity::toStream(stream);
	  
	  stream << "Component [" << m_typename << "] "; 
	  stream << "Configuration: " << m_configuration << std::endl;
	  
	  for (auto prop: m_properties)
		stream << prop << std::endl;
      
      return stream;
  }

  //////////////////////////////////////////////////////////////////////////////////////
    
  void ComponentConfiguration::readPtree(const ptree::Node& ptree)
  {
	 toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
  }

}
}
}
