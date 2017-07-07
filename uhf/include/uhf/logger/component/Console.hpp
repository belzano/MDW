#pragma once

#include "uhf/core/component/ILogger.hpp"

namespace uhf {
namespace component {
namespace logger {

    /////////////////////////////////////////////////////////////////////

    class Console : public ILogger
    {
    public:
		Console();
		virtual ~Console();

		virtual void log(const char*);

    };

    typedef std::shared_ptr<Console> ConsolePtr;
      
}
}
}
