#pragma once

#include <list>
#include <typeinfo>
#include "toolbox/Typename.hpp"
#include "toolbox/Logger.hpp"

namespace toolbox {
namespace bridge {

    template<class TFrom, class TTo>
    void bridge(const TFrom& iObject, TTo& oObject);
// // // 
    ///////////////////////////////////////////////////////////////////////////////////
    
    template <class TFrom, class TTo>
    class Bridge
    {
    public:
	virtual void bridge(const TFrom&, TTo&) = 0;
    };
    
    ///////////////////////////////////////////////////////////////////////////////////

    template <class Object1, class Object2, class attrObject1Type, class attrObject2Type>
    class BridgeAttribute : public Bridge<Object1, Object2>
    {
    public:
	typedef std::unary_function<const attrObject1Type&, Object1> ConstAttributeAccessor;
	typedef std::unary_function<      attrObject2Type&, Object2> AttributeAccessor;

	BridgeAttribute(ConstAttributeAccessor accessor, 
					AttributeAccessor writer)
		: m_accessor(accessor)
		, m_writer(writer)
	{}

	void bridge(const Object1& src, Object2& out) override
	{ 
		bridge(m_accessor(src), m_writer(out));
	}

	AttributeAccessor 	m_writer;
	ConstAttributeAccessor 	m_accessor;
    };

    ///////////////////////////////////////////////////////////////////////////////////

    template <class TFrom, class TTo>
    class BridgeClass : public Bridge<TFrom, TTo>
    {
    public: 
	BridgeClass()
	{}
	
	void bridge(const TFrom& from, TTo& to) override
	{	    
	    for (auto it = m_attributes.begin(), itEnd = m_attributes.end(); it != itEnd; ++it)
	    {
		(*it)->bridge(from, to);
	    }
	}
    
	static BridgeClass*& Instance()
	{
	    static BridgeClass<TFrom,TTo>* instance = nullptr;
	    return instance;
	}
	
	void RegisterBridgeAttribute(Bridge<TFrom, TTo>* iBridgeAttribute)
	{
	    m_attributes.push_back(iBridgeAttribute);
	}
	
	std::list< Bridge<TFrom, TTo>* > m_attributes;
    };

    ///////////////////////////////////////////////////////////////////////////////////

    template <class TFrom, class TTo>
    void RegisterBridge()
    {
	Bridge<TFrom, TTo>*& instance = Bridge<TFrom, TTo>::Instance();
	if (instance == nullptr)
	{
	    MDW_LOG_DEBUG("Creating bridge object from " << type_name<TFrom>() <<  " to " << type_name<TTo>() );
	    instance = new BridgeClass<TFrom, TTo>();
	}
    }

    ///////////////////////////////////////////////////////////////////////////////////

    template <class TFrom, class TTo>
    void RegisterBridgeAttribute(Bridge<TFrom, TTo>* bridgeAttribute)
    {
	BridgeClass<TFrom, TTo>*& instance = BridgeClass<TFrom, TTo>::Instance();
	if (instance == nullptr)
	{
	    MDW_LOG_ERROR("Unable to find bridge object from " << type_name<TFrom>() <<  " to " << type_name<TTo>() << " to register attribute bridge" );
	    instance = new BridgeClass<TFrom, TTo>();
	}
	
	instance->RegisterBridgeAttribute(bridgeAttribute);
    }

    template<class TFrom, class TTo>
    void bridge(const TFrom& iObject, TTo& oObject)
    {
	BridgeClass<TFrom, TTo>* instance = BridgeClass<TFrom, TTo>::Instance();
	if (instance == nullptr)
	{
	    MDW_LOG_ERROR("Unable to find bridge from " << type_name<TFrom>() <<  " to " << type_name<TTo>() );
	    return;
	}
	
	instance->bridge(iObject, oObject);
    }


}
}
