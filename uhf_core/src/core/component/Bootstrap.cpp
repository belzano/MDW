#include "uhf/core/component/Bootstrap.hpp"
#include "BootstrapImpl.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace core {
namespace component {
	
    Bootstrap::Bootstrap(IBrokerPtr broker)
    : IComponent(broker)
    , m_impl(new BootstrapImpl())
    {

    }	

    ////////////////////////////////////////////////////////////

    Bootstrap::~Bootstrap()
    {
	delete m_impl;
    }	

    ////////////////////////////////////////////////////////////

    void Bootstrap::loadComponents(const std::string& configFileName)
    {
	m_impl->loadComponents(configFileName, getBroker());
    }


}
}
}
