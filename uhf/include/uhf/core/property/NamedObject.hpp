#pragma once

#include "uhf/IProperty.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace core {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class NamedObject : public IProperty
    {
    public:
		std::string getName() { 
			return m_name; 
		}
		
		virtual bool equals(IPropertyPtr other) const override;
		
		virtual std::ostream& toStream(std::ostream& stream) const override ;
		
		
	protected:
		std::string m_name;
    };
    
	typedef std::shared_ptr<NamedObject> NamedObjectPtr;

}
}
}
