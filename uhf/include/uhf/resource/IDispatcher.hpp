#pragma once


namespace uhf {	

template<class V>
class IHandler
{
public:
    constexpr static const char* TypeName = "uhf::resource::IHandler" + V::TypeName;

    virtual bool handle(const V&) = 0;
};
  
template<class V>
class IDispatcher
{
public:
    constexpr static const char* TypeName = "uhf::resource::IDispatcher" + V::TypeName;

    virtual bool dispatch(const V&) = 0;
    bool registerHandler(Handler<V>Ptr handler)
    {
        return registerHandler(V::TypeName, handler);
    }
    
    virtual bool registerHandler(const char*, Handler<V>Ptr) = 0;
};

typedef std::shared_ptr<IRunner> IRunnerPtr;

}
