#pragma once

#include "uhf/IComponent.hpp"
#include "uhf/IConsumer.hpp"

namespace uhf {
namespace component {

	template <class T>
	class IProducer : public IComponent
	{   
	public:
		IProducer() : IComponent() {}
		virtual ~IProducer() {}
	 
		virtual int registerConsumer(std::shared_ptr<IConsumer<T>> consumer) = 0;
		//virtual int deregisterConsumer(std::shared_ptr<IConsumer<T>> consumer) = 0;
	};


}
}  // namespace uhf
