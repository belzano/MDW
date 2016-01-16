#pragma once

#include <memory>
#include "wtf/bus/BusMessageDecoder.hpp"
#include "wtf/toolbox/Registry.hpp"
#include "wtf/toolbox/Factory.hpp"

namespace WTF
{		
	class BusMessageDecoderRegistry : public WTF::toolbox::Registry< WTF::toolbox::SharedPtrFactory<BusMessageDecoder > >
	{
		public:
	};
}
