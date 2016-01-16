#pragma once

#include <string>
#include <map>

namespace toolbox
{
	////////////////////////////////////////////////////////////////
	
	class ExecutionContext
	{
		public:		
			
			void init(const std::map<std::string, std::string>& env);
			
			static ExecutionContext& instance();
			
			//  Configuration 	
			// TODO remove
			std::string getDirCfg() const;
			std::string getDirQueues() const;
			std::string getMessageQueueName() const;
			std::string getDirData() const;	
			std::string getDirBin() const;
			std::string getDirLib() const;
			std::string getDirDataTestIn() const;
			std::string getDirDataTestOut() const;
		
			//template <class T> 	public setConfig(std::shared_ptr<const T> config){}
			//template <class T> 	public getConfig(std::shared_ptr<const T> config){}
		
		
		private:
			static ExecutionContext* _instance;
			std::map<std::string, std::string> m_env;
	};

}



