#pragma once

#include "ProcessType.hpp"
#include "Process.hpp"

#include "BackendConfiguration.hpp"
#include "ServerConfiguration.hpp"
#include "DaemonConfiguration.hpp"
#include "BatchConfiguration.hpp"

#include "wtf/toolbox/ExecutionContext.hpp"
 
namespace WTF
{
	template <ProcessType T> struct BackendTypeConfig { };	
	
	template <> struct ProcessTypeConfig<WTF::E_BE_Server> 
	{ typedef WTF::configuration::BackendConfiguration Type; static const char* Filename; };
	
	template <> struct ProcessTypeConfig<WTF::E_BE_Daemon> 			
	{ typedef WTF::configuration::BackendConfiguration Type; static const char* Filename;};
	
	template <> struct ProcessTypeConfig<WTF::E_BE_Batch> 			
	{ typedef WTF::configuration::BackendConfiguration Type; static const char* Filename;};
}

namespace WTF
{
	template <WTF::ProcessType T_ProcessType>
	class Backend : public TypedProcess<T_ProcessType> 
	{
		public:
			Backend(const std::string& name) 
				:TypedProcess<T_ProcessType>(name)
			{}

		protected:		
			virtual void initialize() 	override;
			virtual int activate()		override { return TypedProcess<T_ProcessType>::activate(); }
			
			virtual int deactivate()	override { return TypedProcess<T_ProcessType>::deactivate(); }
			virtual int waitForCompletion()		override { return TypedProcess<T_ProcessType>::waitForCompletion(); }
			
			const typename BackendTypeConfig<T_ProcessType>::Type& getConfiguration() const { return _beConfig; }

		protected:		
			typename BackendTypeConfig<T_ProcessType>::Type _beConfig;
	};

}
/////////////////////////////////////////	

template <WTF::ProcessType T_ProcessType>
void WTF::Backend<T_ProcessType>::initialize()
{
	TypedProcess<T_ProcessType>::initialize();
	
	std::string filename = Process::getProcessConfigurationPath() + "init_be.json";
	WTF_LOG_INFO("Backend::initialize configuration on path" << filename);
	_beConfig.fromJson(filename);
}

