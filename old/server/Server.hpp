#pragma once

#include "HttpTrafficHandler.hpp"

#include "Backend.hpp"
#include "ProcessType.hpp"


namespace WTF
{
		
	template <> struct BackendTypeConfig<E_BE_Server> 		{ typedef configuration::ServerConfiguration Type; };
		
	/////////////////////////////////////////////////////////////////////
		
	class Server : public Backend<ProcessType::E_BE_Server>
	{
		public:
			Server(const std::string& name, int port);
			
			virtual void initialize() override;			
			virtual int activate() override;
			virtual int deactivate() override;
			
		private:
			HttpTrafficHandler  _httpTrafficHandler;
	};

}
