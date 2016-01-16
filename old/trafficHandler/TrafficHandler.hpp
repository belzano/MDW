#pragma once

//#include "wtf/bus/Payload.hpp"

namespace WTF
{
	
	/////////////////////////////////////////////////////////////////////
		
	class TrafficHandler
	{
		public:
		
			TrafficHandler(int port);
			
			int activate();
			int deactivate();
			
		private:
			//BusMessageQueue* m_queue;
			int _port;
			void* daemon = 0;
	};

}
