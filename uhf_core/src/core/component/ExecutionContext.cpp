#include "uhf/core/component/ExecutionContext.hpp"

#include <iostream>

namespace uhf {
namespace core {
namespace component {

/////////////////////////////////////////////////////////////////////

ExecutionContext::ExecutionContext() 
{ 
    char* envVar = ::getenv("APP_ROOT_DIR");
    if (envVar != NULL)
    {
	m_rootDir = std::string(envVar);
    }
    else
    {	    
	std::cout << "env var $APP_ROOT_DIR is not defined: defaulting to current directory.";	
	m_rootDir = std::string("./");	
    }
}

/////////////////////////////////////////////////////////////////////

ExecutionContext::~ExecutionContext() 
{ 

}

/////////////////////////////////////////////////////////////////////

void ExecutionContext::setApplicationRootDir(const std::string& rootDir) 
{ 
  m_rootDir = rootDir;
}

/////////////////////////////////////////////////////////////////////

void ExecutionContext::setApplicationName(const std::string& appName)
{
  m_appName = appName;
}

/////////////////////////////////////////////////////////////////////

std::string ExecutionContext::getConfigurationDir() const
{
  return m_rootDir + "/etc";
} 

/////////////////////////////////////////////////////////////////////

}
}
}
