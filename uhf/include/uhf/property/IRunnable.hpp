#pragma once

#include "toolbox/Types.hpp"
#include "uhf/IProperty.hpp"

namespace uhf {	

class RunnableParameters
{
public:
    bool m_shouldStop;
  
};

typedef std::shared_ptr<const RunnableParameters> RunnableParametersPtr;

// ----------------------------------------------------------------------

class IRunnable : public IProperty
{
public:
    constexpr static const char* TypeName = "uhf::property::IRunnable";

    virtual bool run(RunnableParametersPtr& parameters) = 0;
};

typedef std::shared_ptr<IRunnable> IRunnablePtr;

}
