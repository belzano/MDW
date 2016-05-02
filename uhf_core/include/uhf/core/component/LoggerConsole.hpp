#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/core/ability/Logging.hpp"

namespace uhf {
namespace core {
namespace component {

    class LoggerImpl;

    /////////////////////////////////////////////////////////////////////

    class LoggerConsole : public IComponent, uhf::core::ability::Logging
    {
    public:
	constexpr static const char* TypeName = "uhf::core::component::LoggerConsole";

	LoggerConsole();
	virtual ~LoggerConsole();

	virtual void log(const char*);

    };

    typedef std::shared_ptr<LoggerConsole> LoggerConsolePtr;
      
}
}
}
