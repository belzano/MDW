#pragma once

#include "toolbox/Types.hpp"
#include "toolbox/PtreeHelper.hpp"
#include "toolbox/ObjectModelHelpers.hpp"

class MsgSimpleString : public toolbox::PtreeDocument<MsgSimpleString>
{   
	MAKE_ATTRIBUTE(std::string, Content)

	public:	
	
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
		{		
			MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, Content)
		}	
};
