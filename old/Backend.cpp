
#include "Backend.hpp"

#include "wtf/toolbox/Logger.hpp"
#include "wtf/toolbox/ScopedChrono.hpp"

 
const char* WTF::ProcessTypeConfig<WTF::E_BE_Server>::Filename = "init_be.json";
const char* WTF::ProcessTypeConfig<WTF::E_BE_Daemon>::Filename = "init_be.json";
const char* WTF::ProcessTypeConfig<WTF::E_BE_Batch>::Filename = "init_be.json";

