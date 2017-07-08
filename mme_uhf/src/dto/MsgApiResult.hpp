#pragma once

#include "toolbox/Types.hpp"
#include "toolbox/PtreeHelper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"

class MsgApiResult : public toolbox::PtreeDocument<MsgApiResult>
{   
	MAKE_ATTRIBUTE(toolbox::DataPtr, Image)

	public:	
	
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
		{		
			MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, toolbox::DataPtr, Image)
		}	
};
