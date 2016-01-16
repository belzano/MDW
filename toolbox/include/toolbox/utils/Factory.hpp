#pragma once

#include <memory>

namespace toolbox {

	// Factory base class
	template <class BaseT>
	class SharedPtrFactory
	{
		public:
		virtual std::shared_ptr<BaseT> newInstance() const = 0;
	};

	// Factory templated class
	template <class BaseT, class ExtendedT>
	class SharedPtrFactoryTemplate : public SharedPtrFactory<BaseT>
	{
		public:
		virtual std::shared_ptr<BaseT> newInstance() const
		{
			return std::shared_ptr<BaseT>(new ExtendedT());
		}
	};

}

