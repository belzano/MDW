#pragma once

#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {

    /////////////////////////////////////////////////////////////////////

	template<class InT, class OutT>
    class IProcessor: public IComponent
    {
    public:
		IProcessor();
		virtual ~IProcessor();

		virtual int process(const InT& params, OutT& result) = 0;

    };
    
	template<class InT, class OutT>
    typedef std::shared_ptr<IProcessor<InT, OutT>> IProcessorPtr;
	
}
}
