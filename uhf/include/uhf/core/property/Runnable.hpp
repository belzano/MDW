#pragma once

#include "uhf/IProperty.hpp"
#include "uhf/IComponent.hpp"

#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Conversions.hpp"

namespace uhf {
namespace core {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class Runnable : public IProperty
    {
    public:
		virtual bool checkConsistency(IComponentPtr componentInstance) const override;
		
		virtual bool equals(IPropertyPtr other) const override;
    };
    
	typedef std::shared_ptr<Runnable> RunnablePtr;
}
}
}
