#pragma once

#include "wtf/toolbox/Types.hpp"

namespace WTF
{
	namespace configuration
	{

		typedef enum
		{
			E_Deactivated,
			E_Starting,
			E_Activated
		} 
		ProcessState;

		/////////////////////////////////////////////////////////////////////

		class RuntimeInfo 
		{
			public:
				ProcessState 	_currentState;
				U64				_currentStateTimestamp;
				ProcessState 	_wishedState;
				U64				_wishedStateTimestamp;
				pid_t 			_pid;
		};

	
	}

}
