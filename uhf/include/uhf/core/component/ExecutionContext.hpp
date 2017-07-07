#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/IComponentRegistry.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

    class ExecutionContext : public IComponent
    {
    public:
		ExecutionContext();
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
