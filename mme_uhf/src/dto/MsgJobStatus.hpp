#pragma once

#include "toolbox/Types.hpp"

#include "toolbox/PtreeHelper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"
#include <string>

class MsgJobStatus : public toolbox::PtreeDocument<MsgJobStatus>
{   
	
	MAKE_ATTRIBUTE(std::string, Status)
	MAKE_ATTRIBUTE(std::string, Progression)

	public:	
	
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
		{		
			MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Status)
			MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Progression)
		}	
};
