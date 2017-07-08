#pragma once

#include "uhf/core/component/ILogger.hpp"

namespace uhf {
namespace logger {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class Console : public uhf::component::ILogger
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
