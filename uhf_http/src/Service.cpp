
#include "uhf/http/Service.hpp"

namespace uhf {
namespace http {


Service::Service()	
{

}

///////////////////////////////////////////////////////////////

int Service::invoke(std::shared_ptr<uhf::http::InvocationRequest> iRequest)	
{
	try
	{
		// preInvoke
		if (! preprocess())
		{
			return 0;
		}	
	
		// invoke	
		if (! process(iRequest))
		{
			return 0;
		}
    
		// postInvoke
		if (! postprocess())
		{
			return 0;
		}	
		
		return 0;
	}
	catch (...)
	{
	
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////

int Service::preprocess() 
{
	return 0;
}

///////////////////////////////////////////////////////////////

int Service::postprocess() 
{
	return 0;
}

///////////////////////////////////////////////////////////////


}
}
