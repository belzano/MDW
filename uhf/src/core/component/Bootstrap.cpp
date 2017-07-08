#include "uhf/core/component/Bootstrap.hpp"
#include "BootstrapImpl.hpp"
#include "toolbox/Logger.hpp"

#include "uhf/core/aspects/IActivable.hpp"
#include "uhf/core/property/Activable.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace component {
	
    Bootstrap::Bootstrap()
    : IRunnable()
    , m_impl(new BootstrapImpl())
    {

    }	

    ////////////////////////////////////////////////////////////

    Bootstrap::~Bootstrap()
    {
		delete m_impl;
    }	

    ////////////////////////////////////////////////////////////

    void Bootstrap::setBootstrapFile(const std::string& configFileName)
    {
		m_impl->setBootstrapFile(configFileName);
    }

    ////////////////////////////////////////////////////////////

    void Bootstrap::run()
    {
		// Create and insert components
		m_impl->doBootstrap(getComponentRegistry());
		
		// Activate Activable components
		std::list<IComponentPtr> components;
		getComponentRegistry()->getComponents(components);
		MDW_LOG_INFO("Looking for activable components (" << components.size() << " to verify)");
		for (auto comp : components) 
		{
			if (comp->hasProperty<uhf::core::property::Activable>())
			{		

				uhf::component::IActivablePtr activableComp = std::dynamic_pointer_cast<uhf::component::IActivable>(comp);
				if (!activableComp->isActive())
				{
					MDW_LOG_INFO("Activating " << comp->getTypename());
					activableComp->activate();
				}
			}
		}
    }

}
}
