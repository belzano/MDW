#pragma once

#include <map>
#include <set>
#include <list>
#include <string>

#include "wtf/toolbox/Types.hpp"
#include "wtf/toolbox/PtreeHelper.hpp"
#include "wtf/toolbox/ObjectModelHelpers.hpp"

#include "ProcessType.hpp"

namespace WTF
{
 
	namespace configuration
	{

		typedef enum
		{
			E_Deactivated,
			E_Starting,
			E_Activated
		} 
		BackendState;

		/////////////////////////////////////////////////////////////////////

		class RuntimeInfo : public toolbox::PtreeDocument<RuntimeInfo>
		{
			WTF_ATTRIBUTE(U64, ProcessId )
			WTF_ATTRIBUTE(U64, CurrentState)
			
		public:

			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, U64, ProcessId )
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, U64, CurrentState)
			}
			/*
			WTF_ATTRIBUTE(std::string, Name)
				
			public:
				BackendState 	_currentState;
				U64				_currentStateTimestamp;
				BackendState 	_wishedState;
				U64				_wishedStateTimestamp;
				pid_t 			_pid;
				*/
		};

		/////////////////////////////////////////////////////////////////////

		class ProcessDescription : public toolbox::PtreeDocument<ProcessDescription>
		{
			WTF_ATTRIBUTE(ProcessType, ProcessType)
			WTF_ATTRIBUTE(std::string, Name)
			WTF_ATTRIBUTE(RuntimeInfo, RuntimeInfo)
			
		public:

			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, ProcessType, ProcessType)
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Name)
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, RuntimeInfo, RuntimeInfo)
			}	
		};

		/////////////////////////////////////////////////////////////////////

		class ApplicationServerNodeStatus : public toolbox::PtreeDocument<ApplicationServerNodeStatus>
		{
			WTF_ATTRIBUTE( std::list< ProcessDescription> , Processes)
		
		public:

			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::list< ProcessDescription> , Processes)
			}		
		};

		/////////////////////////////////////////////////////////////////////

/*
		template <ProcessType T>
		class BackendInstanceDescriptor
		{
			public:
				BackendInstanceDescriptor()
				: _type(T) {}
			
				ProcessType 	_type;
				std::string 	_name;
				//typename BackendConfig<T>::Type _config;
				RuntimeInfo 	_runtimeInfo;
		};

		/////////////////////////////////////////////////////////////////////

		class NodeInstanceDescriptor
		{
			public:
				BackendInstanceDescriptor<E_Agent>						_mag;
				BackendInstanceDescriptor<E_FrontEnd> 					_fe;
				std::list< BackendInstanceDescriptor<E_BE_Server> >		_servers;
				std::list< BackendInstanceDescriptor<E_BE_Daemon> >		_daemons;
				std::list< BackendInstanceDescriptor<E_BE_Batch> >		_batches;	
		};
*/
	}
}

WTF_DECLARE_PTREE_SERIALIZER_LIST(WTF::configuration::ProcessDescription)
