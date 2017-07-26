#pragma once

#include "uhf/bus/component/Listener.hpp"
#include "uhf/bus/Instruction.hpp"
//#include "uhf/IComponentRegistry.hpp"
#include <memory>

namespace uhf {
namespace bus {
namespace component {
		
	/////////////////////////////////////////////////////////////////////
		
	class InstructionListener : public Listener<Instruction>
	{
	public:
		InstructionListener() {}
		~InstructionListener() {}

	protected:	
		virtual void onMessageReceived(Message<Instruction> ) override {
			// TODO call message.get()->run()
		}
	};
	
}
}
}
