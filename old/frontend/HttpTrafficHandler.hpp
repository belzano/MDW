#pragma once

namespace WTF
{
	/////////////////////////////////////////////////////////////////////
		
	class HttpTrafficHandler
	{
		public:
		
			HttpTrafficHandler(int port);
			
			int activate();
			int deactivate();
			
		private:
			int _port;
			void* daemon = 0;
	};

}
