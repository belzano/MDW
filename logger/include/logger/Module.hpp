#pragma once

#include <memory>
#include "logger/Configuration.hpp"

namespace logger
{
	class Manager;
	
	class Module
	{
		public:
			static Module& Instance();
			
			void activate();
			void deactivate();
						
			void setConfiguration(std::shared_ptr<Configuration> config);
			std::shared_ptr<Configuration> getConfiguration();
			
			Manager& getManager();
			
		private:
			Module();
			~Module();
		
			std::shared_ptr<Configuration> _config;
			Manager* _manager;
	};
	
}


