#pragma once


#include "uhf/IComponent.hpp"

namespace uhf {
namespace component {

	template <class T>
	class IConsumer : public IComponent
	{   
	public:
		IConsumer() : IComponent() {}
		virtual ~IConsumer() {}
	 
		virtual int consume(std::shared_ptr<T> request) = 0;
	};


}
}  // namespace uhf
