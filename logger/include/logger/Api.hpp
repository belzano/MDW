#pragma once

#include "logger/Stream.hpp"
#include "logger/Stack.hpp"

namespace logger{
  
class Api
{
public:
    static Stream& ThreadInstance();
    static Stack& ThreadStack();
};

}


