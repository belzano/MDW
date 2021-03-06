
#include "BootstrapConfiguration.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::bootstrap::configuration::BootstrapConfiguration)

using namespace toolbox;
    
namespace uhf{
namespace bootstrap{
namespace configuration{

  void BootstrapConfiguration::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
	  toolbox::ptree::bridge("version", ptree, m_version);
      toolbox::ptree::bridge("libraries", ptree, m_libraries);
      toolbox::ptree::bridge("components", ptree, m_components);
  }
	
  //////////////////////////////////////////////////////////////////////////////////////
  
  std::ostream& BootstrapConfiguration::toStream(std::ostream& stream) const 
  {
	PtreeEntity::toStream(stream);

	stream << "Bootstrap version:" << m_version << "] ;";
	stream << " Libraries: ";
	for (auto lib: m_libraries)
		stream << lib << "; " << std::endl;
	stream << " Components: ";
	//for (auto comp: m_components)
	//	stream << comp << std::endl;
	return stream;
  }
	
  //////////////////////////////////////////////////////////////////////////////////////
    
}
}
}
