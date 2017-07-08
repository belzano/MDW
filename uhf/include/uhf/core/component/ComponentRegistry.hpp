#pragma once

#include "uhf/IComponentRegistry.hpp"
#include "uhf/core/component/IActivable.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class ComponentRegistry : public IComponentRegistry, public IActivable
    {
    public:
		ComponentRegistry();
		virtual ~ComponentRegistry();

		void getComponents(std::list<IComponentPtr>& components) const override;

		void onActivate() override;
		void onPassivate() override;

	protected:
		IComponentPtr getComponent(const uhf::ComponentTypeName& componentName) override;
		void registerComponent(IComponentPtr component) override;
		
		virtual std::ostream& toStream(std::ostream& stream) const override;
		
    private:
		std::list<IComponentPtr> m_components;
    };

    typedef std::shared_ptr<ComponentRegistry> ComponentRegistryPtr;
}
}
