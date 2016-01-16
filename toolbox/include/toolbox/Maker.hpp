#pragma once

#include <string>
#include <memory>
#include <map>

namespace toolbox {
 
    /////////////////////////////////////////////////////////////////////////////////
  
    class Object
    {
    public:
	virtual ~Object(){}
    };
  
    /////////////////////////////////////////////////////////////////////////////////
  
    class ObjectMaker
    {
    public:
	virtual std::shared_ptr<Object> make() = 0;
    };
  
    template <class T>
    class ObjectMakerImpl : public ObjectMaker
    {
    public:
	virtual std::shared_ptr<Object> make() override
	{ 
	  return std::shared_ptr<Object>(new T());
	}
    };
    
    typedef std::shared_ptr<ObjectMaker> ObjectMakerPtr;
    
    /////////////////////////////////////////////////////////////////////////////////
    
    class Maker
    {
    public:
     
        // singleton 
	static Maker& instance();
      
	typedef std::string Key;
	
	template <class T>
	void registration()
	{
	    ObjectMakerPtr objMaker(new ObjectMakerImpl<T>());
	    registration(T::TypeName, objMaker);
	}
	
	void registration(const Key& key, ObjectMakerPtr& maker);

	
	template <class T>
	std::shared_ptr<T> make(const Key& key)
	{
	    std::shared_ptr<Object> ptr = do_make(key);
	    return std::dynamic_pointer_cast<T>(ptr);
	}

	template <class T>
	std::shared_ptr<T> make()
	{
	    return make(T::TypeName);
	}

    private:
	Maker(){}
	Maker(const Maker&);
      
	std::shared_ptr<Object> do_make(Key const& key);
      
	typedef std::map<Key, ObjectMakerPtr> ObjectMakerRegistry;
	ObjectMakerRegistry _makers;
    };
      
}

#define MDW_REGISTER_OBJECT_MAKER(type)\
  MDW_ON_LIBRARY_LOAD(toolbox::Maker::instance().registration<type>())

