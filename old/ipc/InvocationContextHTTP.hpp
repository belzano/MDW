#pragma once

#include "wtf/toolbox/Types.hpp"
#include "wtf/api/InvocationContext.hpp"

#include <string>

namespace WTF
{
	class InvocationContextHTTP : public InvocationContext
	{
		
	public:
		InvocationContextHTTP(TriggerType);
		
		virtual void reply(Payload*) override;
		
	protected:
		std::string m_url;
	};		
}

