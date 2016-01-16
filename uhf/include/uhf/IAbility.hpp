#pragma once

#include <string>
#include "toolbox/Types.hpp"

namespace uhf {	

class IAbility
{
public:
    IAbility();
    virtual ~IAbility();
};

typedef std::shared_ptr<IAbility> IAbilityPtr;

}
