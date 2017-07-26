#pragma once

#include "toolbox/Logger.hpp"
#include "toolbox/Types.hpp"
#include "toolbox/Base64.hpp"

namespace uhf {
namespace bus {

	typedef toolbox::DataPtr DataPtr;

	class MessageQueue {
		
	public:
		MessageQueue(const std::string& name);
	
		DataPtr tryDequeue();
		bool queue(DataPtr iJob);
		
	private:
		std::string _name;
		U32 _maxMsgSize;
		U32 _maxQueueSize;
	};

	
}
}
