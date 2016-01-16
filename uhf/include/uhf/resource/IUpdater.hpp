#pragma once

#include <string>
#include "toolbox/Types.hpp"

namespace uhf {	

class IUpdater
{
public:
    constexpr static const char* TypeName = "uhf::resource::IUpdater";
    
    virtual void registerForUpdate(IUpdatablePtr) = 0;
};

typedef std::shared_ptr<IUpdater> IUpdaterPtr;

}
