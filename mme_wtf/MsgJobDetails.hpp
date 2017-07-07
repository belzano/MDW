#pragma once

#include "toolbox/Types.hpp"
#include "toolbox/PtreeHelper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"

#include "MsgJobStatus.hpp"
#include "MsgApiResult.hpp"

class MsgJobDetails : public toolbox::PtreeDocument<MsgJobDetails>
{   
	
	MAKE_ATTRIBUTE(std::string, JobId)
	MAKE_ATTRIBUTE(MsgJobStatus, Status)
	MAKE_ATTRIBUTE(MsgApiResult, Result)	
		
	public:
	
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
		{		
			MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, JobId)
			MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, MsgJobStatus, Status)
			MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, MsgApiResult, Result)
		}
	
};
