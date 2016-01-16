#pragma once

#include "BusMessage.hpp"

namespace WTF
{
	/////////////////////////////////////////////////////////////////////
		
	class ShutdownRequest : public BusMessage
	{
		public:
			ShutdownRequest()
				: BusMessage("CMD:SHUTDOWN")
			{}
	};
}
