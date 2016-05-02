#pragma once

#include "uhf/IComponent.hpp"

namespace uhf {
namespace core {
namespace component {

    class RunnerImpl;

    /////////////////////////////////////////////////////////////////////

    class Runner: public IComponent
    {
    public:
	constexpr static const char* TypeName = "uhf::core::component::Runner";

	Runner();
	virtual ~Runner();

	int run();
	void requestShutdown(){}

    private:
	RunnerImpl* m_impl;
    };

    typedef std::shared_ptr<Runner> RunnerPtr;
	
}
}
}
