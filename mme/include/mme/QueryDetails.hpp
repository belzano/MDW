#pragma once

#include <string>
#include <memory>
#include "toolbox/Image.hpp"

#include "toolbox/StorageCell.hpp"
#include "toolbox/PtreeHelper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"

namespace API
{
	
	/////////////////////////////////////////////////////////////
	
	class Requestor : public toolbox::PtreeDocument<Requestor>
	{
		public:	
			Requestor()
				: toolbox::PtreeDocument<Requestor>()
				{}
		
			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, HwId)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, HwNativeResolution)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, OsName)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, OsVersion)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, ClientSwVersion)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, ClientSw)
			}
			
			MAKE_ATTRIBUTE(std::string, HwId)
			MAKE_ATTRIBUTE(std::string, HwNativeResolution)
			MAKE_ATTRIBUTE(std::string, OsName)
			MAKE_ATTRIBUTE(std::string, OsVersion)	
			MAKE_ATTRIBUTE(std::string, ClientSwVersion)
			MAKE_ATTRIBUTE(std::string, ClientSw)
	};
	
	/////////////////////////////////////////////////////////////
	
	class InputDetails : public toolbox::PtreeDocument<InputDetails>
	{
		public:	
			InputDetails()
				: toolbox::PtreeDocument<InputDetails>()
				{}
				
			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Name)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Resolution)
			}
		
			MAKE_ATTRIBUTE(std::string, Name)
			MAKE_ATTRIBUTE(std::string, Resolution)		
	};
	
	/////////////////////////////////////////////////////////////
	
	class Events : public toolbox::PtreeDocument<Events>
	{
		public:	
			Events()
				: toolbox::PtreeDocument<Events>()
				{}				
				
			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, QueueingTimestamp)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, TriggerTimestamp)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, CompletionTimestamp)	
			}		
			
			MAKE_ATTRIBUTE(std::string, QueueingTimestamp)
			MAKE_ATTRIBUTE(std::string, TriggerTimestamp)
			MAKE_ATTRIBUTE(std::string, CompletionTimestamp)
	};

	/////////////////////////////////////////////////////////////
	
	class State : public toolbox::PtreeDocument<State>
	{
		public:	
			State()
				: toolbox::PtreeDocument<State>()
				{}
				
			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Status)
				MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Progression)
			}
		
			MAKE_ATTRIBUTE(std::string, Status)
			MAKE_ATTRIBUTE(std::string, Progression)
	};
	
	/////////////////////////////////////////////////////////////	
}
