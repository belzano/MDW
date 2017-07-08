#pragma once

#include <string>
#include <memory>
#include <map>

#include "uhf/IComponent.hpp"
#include "uhf/IComponentMaker.hpp"

namespace uhf {
namespace core {

template <class ComponentT>
class ComponentMakerTemplate : public uhf::IComponentMaker
{
	public:
	virtual IComponentPtr make() const override
	{
		return IComponentPtr(new ComponentT());
	}
};

//////////////////////////////////////////////////////////////////////

class ComponentMakerRegistry
{
public:
    
    bool isRegistered(const uhf::ComponentTypeName&) const;
    
    IComponentMakerPtr getComponentMaker(const uhf::ComponentTypeName&) const;

    void registerComponentMaker(const uhf::ComponentTypeName& componentName, 
						        IComponentMakerPtr iComponentMaker);

	template<class ComponentT>
	static void registerComponentMaker()
	{
		uhf::ComponentTypeName name = uhf::IComponent::getTypename<ComponentT>();
		uhf::IComponentMakerPtr makerPtr(new ComponentMakerTemplate<ComponentT>());
		instance().registerComponentMaker(name, makerPtr);
	}

	static ComponentMakerRegistry& instance();

private:

	std::map<std::string, IComponentMakerPtr > _makers;

};

//////////////////////////////////////////////////////////////////////

#define UHF_COMPONENT_MAKER_REGISTRATION( ComponentP )\
void (*loader##ComponentP)(void) __attribute__ ((section (".ctors"))) \
			= uhf::core::ComponentMakerRegistry::registerComponentMaker<ComponentP>;

} 
}


