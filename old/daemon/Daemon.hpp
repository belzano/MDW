#pragma once


#include "Backend.hpp"
#include "ProcessType.hpp"

namespace WTF
{
		
	template <> struct BackendTypeConfig<E_BE_Daemon> 		{ typedef configuration::DaemonConfiguration Type; };
		
	/////////////////////////////////////////////////////////////////////
		
	class Daemon : public Backend<ProcessType::E_BE_Daemon>
	{
		public:
		
			Daemon(const std::string& name);
			virtual void initialize() override;
	};

}
