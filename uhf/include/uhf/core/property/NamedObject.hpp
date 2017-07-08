#pragma once

#include "uhf/core/property/PtreeProperty.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace core {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class NamedObject : public PtreeProperty
    {
    public:
		std::string getName() { 
			return m_name; 
		}
		
		virtual void readPtree(const toolbox::ptree::Node&) override;

		virtual std::ostream& toStream(std::ostream& stream) const override ;
		
	private:
		std::string m_name;
    };
    
	typedef std::shared_ptr<NamedObject> NamedObjectPtr;

}
}
}

MDW_PTREE_CONVERSION_ENTITY_DECLARE(uhf::core::property::NamedObject)
