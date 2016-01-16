#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/IBroker.hpp"

namespace uhf {
namespace core {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class ExecutionContext : public IComponent
    {
    public:
	constexpr static const char* TypeName = "uhf::core::component::ExecutionContext";

	ExecutionContext(IBrokerPtr broker);
	virtual ~ExecutionContext();
	

	void setApplicationRootDir(const std::string& rootDir);
	void setApplicationName(const std::string& appName);
	
	std::string getConfigurationDir() const;
	
    private:
	std::string m_rootDir;
	std::string m_appName;
    };

    typedef std::shared_ptr<ExecutionContext> ExecutionContextPtr;
}
}
}