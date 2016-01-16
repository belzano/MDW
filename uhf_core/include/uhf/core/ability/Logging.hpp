#pragma once

#include "uhf/IAbility.hpp"

namespace uhf {
namespace core {
namespace ability {
	
    /////////////////////////////////////////////////////////////////////

    class Logging : public IAbility
    {
    public:
	constexpr static const char* TypeName = "uhf::core::ability::Logging";

	virtual void log(const char*) = 0;
    };
}
}
}
