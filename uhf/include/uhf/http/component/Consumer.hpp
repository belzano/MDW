#pragma once

#include "uhf/core/component/IConsumer.hpp"
#include "uhf/http/InvocationRequest.hpp"
#include "toolbox/Types.hpp"

#include <string>
#include <map>

namespace uhf {
namespace component {
namespace http {
	
	typedef uhf::http::InvocationRequest InvocationRequest;
	
	//////////////////////////////////////////////////////////
	
	class Consumer : public uhf::component::IConsumer<InvocationRequest>
	{   
	public:		
		Consumer();
		virtual ~Consumer();
		
		int consume(std::shared_ptr<InvocationRequest>) override;
		
	protected:	
		virtual int preprocess();
		
		virtual int process(std::shared_ptr<InvocationRequest>) = 0;

		virtual int postprocess();
		
	private:
		//ServiceContext m_context;

	};


}
}
}  // namespace uhf
