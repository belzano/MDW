
#include "uhf/core/command/Activator.hpp"

#include "toolbox/Logger.hpp"

#include "uhf/core/component/ComponentRegistry.hpp"
#include "uhf/core/aspects/IActivable.hpp"
#include "uhf/core/property/Activable.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace command {
	
    Activator::Activator()
	{

    }	

    ////////////////////////////////////////////////////////////

    Activator::~Activator()
    {

    }	

    ////////////////////////////////////////////////////////////

    bool Activator::activateComponents(uhf::IComponentRegistryPtr registry)
    {
		uhf::core::property::ActivablePtr activableProperty(new uhf::core::property::Activable());
		
		std::list<IComponentPtr> components;
		registry->getComponents(components);
		MDW_LOG_DEBUG("Looking for activable components (" << components.size() << " to verify)");
		for (auto comp : components) 
		{
			MDW_LOG_DEBUG("Checking (" << comp->getTypename());
			if (! comp->hasProperty(activableProperty))
			{	
				MDW_LOG_DEBUG("Component (" << comp->getTypename() << " is not activable");
				continue;	
			}
			
			uhf::component::IActivablePtr activableComp = std::dynamic_pointer_cast<uhf::component::IActivable>(comp);
			if (activableComp->isActive())
			{
				MDW_LOG_DEBUG("Component (" << comp->getTypename() << " is already active: Skipping");
				continue;
			}
				
			MDW_LOG_INFO("Activating " << comp->getTypename());
			activableComp->activate();
		}
		return true;
    }
    
}
}
