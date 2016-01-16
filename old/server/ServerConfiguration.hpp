#pragma once

#include <map>
#include <set>
#include <list>
#include <string>

#include "wtf/toolbox/Types.hpp"
#include "wtf/toolbox/PtreeHelper.hpp"
#include "wtf/toolbox/ObjectModelHelpers.hpp"

#include "ServiceConfiguration.hpp"

namespace WTF
{

namespace configuration
{
	/////////////////////////////////////////////////////////////////////

	class ServerConfiguration : public toolbox::PtreeDocument<ServerConfiguration>
	{
		typedef std::map< std::string, ServiceConfiguration> ServiceMapping;
		WTF_ATTRIBUTE( ServiceMapping , Handlers)
		WTF_ATTRIBUTE(ServiceConfiguration, DefaultHandler)
		
	public:
	
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
		{		
			WTF_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, ServiceConfiguration, DefaultHandler)
		}
	};
	
	}

}
