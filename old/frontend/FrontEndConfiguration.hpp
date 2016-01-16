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

		class FrontEndConfiguration : public toolbox::PtreeDocument<FrontEndConfiguration>
		{
			WTF_ATTRIBUTE( std::string , Default)
		
		public:

			template <class K>
			static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
			{		
				WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string , Default)
			}		
		};

	}
}

//WTF_DECLARE_PTREE_SERIALIZER_LIST(WTF::configuration::ProcessDescription)
