#include "uhf/bootstrap/component/Bootstrap.hpp"
#include "uhf/bootstrap/command/Bootstrap.hpp"
#include "toolbox/Logger.hpp"

#include "uhf/core/aspects/IActivable.hpp"
#include "uhf/core/property/Activable.hpp"

////////////////////////////////////////////////////////////

namespace uhf {
namespace component {
	
    Bootstrap::Bootstrap()
	{

    }	

    ////////////////////////////////////////////////////////////

    Bootstrap::~Bootstrap()
    {

    }	

    ////////////////////////////////////////////////////////////

    void Bootstrap::setBootstrapFile(const std::string& bootstrapFilename)
    {
		_bootstrapFilename = bootstrapFilename;
    }

    ////////////////////////////////////////////////////////////

    void Bootstrap::onActivate()
    {
		// Create and insert components
		uhf::command::Bootstrap().doBootstrap(_bootstrapFilename, getComponentRegistry());
    }
    
    ////////////////////////////////////////////////////////////

	void Bootstrap::onPassivate()
    {
		
    }

}
}
