#pragma once

#include "toolbox/Types.hpp"
#include "uhf/IProperty.hpp"

namespace uhf {	


class UpdateEventArgs
{
    
};
 
// ---------------------------------------------------------------------
 
class IUpdatable: public IProperty
{
public:
    constexpr static const char* TypeName = "uhf::property::IUpdatable";

    virtual bool update(const UpdateEventArgs& args) = 0;
};

typedef std::shared_ptr<IUpdatable> IUpdatablePtr;

}
