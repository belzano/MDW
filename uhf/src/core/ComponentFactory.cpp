
#include "uhf/core/ComponentFactory.hpp"
#include "uhf/core/ComponentMakerRegistry.hpp"
#include "toolbox/Logger.hpp"
#include <list>


namespace uhf {
namespace core {
  
    /////////////////////////////////////////////////////////////////////////////////

    ComponentFactory& ComponentFactory::instance()
    {
		static ComponentFactory instance;
		return instance;
    }

    /////////////////////////////////////////////////////////////////////////////////

    uhf::IComponentPtr ComponentFactory::make(uhf::ComponentTypeName const& componentName)
    {
		IComponentMakerPtr makerPtr = ComponentMakerRegistry::instance().getComponentMaker(componentName);
		if (makerPtr.get() == NULL) {
			MDW_LOG_ERROR("No maker registered to create component [" << componentName << "]");
			return uhf::IComponentPtr(nullptr); 
		}
		
		return makerPtr->make();
	}
      
}
}

