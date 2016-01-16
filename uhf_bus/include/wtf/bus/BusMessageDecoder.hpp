#pragma once

#include <memory>
#include "wtf/bus/BusMessage.hpp"

namespace WTF
{
	class Payload;
			
	class BusMessageDecoder
	{
		public:
			virtual std::shared_ptr<BusMessage> decode(Payload* iPayload) const = 0;
	};
}
