#pragma once

#include <map>
#include <set>
#include <list>
#include <string>

#include "wtf/toolbox/Types.hpp"
#include "wtf/toolbox/PtreeHelper.hpp"
#include "wtf/toolbox/ObjectModelHelpers.hpp"

namespace WTF
{

namespace configuration
{
	/////////////////////////////////////////////////////////////////////

	class DaemonConfiguration : public toolbox::PtreeDocument<DaemonConfiguration>
	{
	public:
	
		template <class K>
		static void registerConversions(toolbox::PtreeDocumentConversions<K>& /*registry*/)
		{		
		}
	};
	
	}

}
