
#include "TrafficHandlerConfiguration.hpp"
#include "toolbox/ptree/Helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////

MDW_PTREE_CONVERSION_ENTITY_DEFINE(uhf::http::TrafficHandlerConfiguration)
using namespace toolbox;
    
namespace uhf{
namespace http{

  void TrafficHandlerConfiguration::readPtree(const ptree::Node& ptree)
  {
	  toolbox::ptree::PtreeEntity::readPtree(ptree);
	  
	  toolbox::ptree::bridge("port", ptree, m_port);
  }
      
    //////////////////////////////////////////////////////////////////////////////////////

  std::ostream& TrafficHandlerConfiguration::toStream(std::ostream& stream) const 
  {
	  PtreeEntity::toStream(stream);
	  
	  stream << " TrafficHandlerConfiguration port [" << m_port << "]" << std::endl;
	  return stream;
  }
	
  //////////////////////////////////////////////////////////////////////////////////////
    
}
}
