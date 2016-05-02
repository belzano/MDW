#pragma once 

#include "toolbox/Types.hpp"
#include "toolbox/entity/Entity.hpp"
#include <boost/property_tree/ptree.hpp>

namespace toolbox{
namespace ptree {
	typedef boost::property_tree::ptree Node;
  
	class PtreeEntity: public entity::Entity
	{
	public:
		virtual void writePtree(Node&) const {}
		virtual void readPtree(const Node&) {}
		
		virtual std::ostream& toStream(std::ostream& stream) const override { return stream;}
	};
	
	typedef std::shared_ptr<PtreeEntity> PtreeEntityPtr;
}
}
