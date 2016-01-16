#pragma once

#include "BusMessage.hpp"

namespace WTF
{
	/////////////////////////////////////////////////////////////////////
		
	class Heartbeat : public BusMessage
	{
		public:
			ShutdownRequest()
				: BusMessage("NTF:HEARTBEAT")
			{}
	};
}
