#pragma once

#include "wtf/http/Service.hpp"

namespace WTF
{

class ServiceFactory
{
	public:
	virtual std::shared_ptr<Service> newInstance() const = 0;
};

template <class T>
class ServiceFactoryTemplate : public ServiceFactory
{
	public:
	virtual std::shared_ptr<Service> newInstance() const
	{
		return std::shared_ptr<Service>(new T());
	}
};

}  // namespace WTF
