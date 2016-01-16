#pragma once

#include "uhf/IBroker.hpp"

namespace uhf {
namespace core {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class Broker : public IBroker
    {
    public:
	constexpr static const char* TypeName = "uhf::core::component::Broker";
	
	Broker();
	virtual ~Broker();

	void getComponents(std::list<IComponentPtr>& components) override;

    protected:
	IComponentPtr getComponentInstance(const std::string& componentName) override;
	void registerComponentInstance(const std::string& componentName, IComponentPtr component) override;

    private:
	std::map<std::string, IComponentPtr> m_components;
    };

    typedef std::shared_ptr<Broker> BrokerPtr;
}
}
}
