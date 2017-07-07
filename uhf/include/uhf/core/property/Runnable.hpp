#pragma once

#include "uhf/IProperty.hpp"

namespace uhf {
namespace core {
namespace property {
	
    /////////////////////////////////////////////////////////////////////

    class Runnable : public IProperty
    {
    public:
	constexpr static const char* TypeName = "uhf::core::ability::Logging";

	virtual void log(const char*) = 0;
    };
}
}
}
