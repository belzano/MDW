#pragma once

#include "uhf/IComponentRegistry.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class ComponentRegistry : public IComponentRegistry
    {
    public:
		ComponentRegistry();
		virtual ~ComponentRegistry();

		void getComponents(std::list<IComponentPtr>& components) override;

	protected:
		IComponentPtr getComponentInstance(const uhf::ComponentTypeName& componentName) override;
		void registerComponentInstance(const uhf::ComponentTypeName& componentName, IComponentPtr component) override;

    private:
		std::map<std::string, IComponentPtr> m_components;
    };

    typedef std::shared_ptr<ComponentRegistry> ComponentRegistryPtr;
}
}
