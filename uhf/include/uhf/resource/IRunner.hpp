#pragma once

#include "uhf/IRunnable.hpp"

namespace uhf {	

class IRunner
{
public:
    constexpr static const char* TypeName = "uhf::resource::IRunner";

    virtual void execute(IRunnablePtr) = 0;
};

typedef std::shared_ptr<IRunner> IRunnerPtr;

}
