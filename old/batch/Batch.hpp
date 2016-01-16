#pragma once

#include "Backend.hpp"
#include "ProcessType.hpp"

namespace WTF
{		
	template <> struct BackendTypeConfig<E_BE_Batch> 		{ typedef configuration::BatchConfiguration Type; };
		
	/////////////////////////////////////////////////////////////////////
		
	class Batch : public Backend<ProcessType::E_BE_Batch>
	{
		public:		
			Batch(const std::string& name);
			virtual int activate() override;
			virtual void initialize() override;
	};

}
