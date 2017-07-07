#pragma once

#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {

    class RunnerImpl;

    /////////////////////////////////////////////////////////////////////

    class Runner: public IComponent
    {
    public:
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
