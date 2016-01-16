#pragma once 

#include "Process.hpp"
#include "ProcessType.hpp"

#include "FrontEndConfiguration.hpp"

namespace WTF
{

	/////////////////////////////////////////////////////////////////////

	template <> struct ProcessTypeConfig<WTF::E_FrontEnd> 
	{ typedef WTF::configuration::FrontEndConfiguration Type; static const char* Filename; };

	/////////////////////////////////////////////////////////////////////

	class FrontEnd : public TypedProcess<ProcessType::E_FrontEnd>
	{
		public:	
			FrontEnd();
			
			virtual void initialize() override;
			virtual int activate() override;
			virtual int watchdog() override;
			virtual int deactivate() override;
			virtual int waitForCompletion() override;
			
		private:
			
	};

}
