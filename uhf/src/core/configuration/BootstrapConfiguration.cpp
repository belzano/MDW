
#include "BootstrapConfiguration.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::core::configuration::BootstrapConfiguration)

using namespace toolbox;
    
namespace uhf{
namespace core{
namespace configuration{

  void BootstrapConfiguration::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
	  toolbox::ptree::bridge("version", ptree, m_version);
      toolbox::ptree::bridge("components", ptree, m_components);
  }
	
  //////////////////////////////////////////////////////////////////////////////////////
  
  std::ostream& BootstrapConfiguration::toStream(std::ostream& stream) const 
  {
	  PtreeEntity::toStream(stream);
	  
	  stream << "Bootstrap version [" << m_version << "]" << std::endl;
	  for (auto comp: m_components)
		stream << comp << std::endl;
	  return stream;
  }
	
  //////////////////////////////////////////////////////////////////////////////////////
    
}
}
}
