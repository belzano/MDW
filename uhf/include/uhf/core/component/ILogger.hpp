#pragma once

#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class ILogger : public IComponent
    {
    public:
		ILogger() {}
		virtual ~ILogger() {} 

		virtual void log(const char*) = 0;

    };

    typedef std::shared_ptr<ILogger> ILoggerPtr;
      
}
}
