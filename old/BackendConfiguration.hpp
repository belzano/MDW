#pragma once

#include <set>

#include <wtf/toolbox/Types.hpp>
#include <wtf/toolbox/PtreeHelper.hpp>
#include <wtf/toolbox/ObjectModelHelpers.hpp>

namespace WTF
{
	namespace configuration
	{		
		/////////////////////////////////////////////////////////////////////

		class BackendConfiguration : public toolbox::PtreeDocument<BackendConfiguration>
		{
			WTF_ATTRIBUTE(std::set<std::string>, Libraries)
			
		public:
			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::set<std::string>, Libraries)
			}	
		};
	
	}
}
