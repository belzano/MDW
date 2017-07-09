#include "uhf/core/command/Bootstrap.hpp"
#include "Bootstrap.hpp"
#include "toolbox/Logger.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace command {
	
    Bootstrap::Bootstrap()
	{

    }	

    ////////////////////////////////////////////////////////////

    Bootstrap::~Bootstrap()
    {

    }	

    ////////////////////////////////////////////////////////////

    bool Bootstrap::doBootstrap(const std::string& bootstrapFile, uhf::IComponentRegistryPtr registry)
    {
		return uhf::manager::Bootstrap().doBootstrap(bootstrapFile, registry);
    }
    
}
}
