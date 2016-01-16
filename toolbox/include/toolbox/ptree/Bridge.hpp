#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>

#include "toolbox/Types.hpp"
#include "toolbox/Logger.hpp"
#include "toolbox/Maker.hpp"

#include "toolbox/bridge/Bridge.hpp"
#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Specializations.hpp"

#include <boost/foreach.hpp>

namespace toolbox {
    
    enum class ValueType
    {
      E_Plain,
      E_Pointer,
      E_StdSharedPtr,
    };
      
    enum class ContainerType
    {
      E_Value,
      E_StdList,
      E_StdVector,
      E_StdSet,
      E_StdMap
    };
  
namespace ptree {


  
    ///////////////////////////////////////////////////////////////////////////////////

    template <class TType>
    class BridgePtreeClassPtr : public bridge::BridgeClass<ptree, std::shared_ptr<TType> >,
				public bridge::BridgeClass<std::shared_ptr<TType>, ptree >
    {
    public: 
	BridgePtreeClassPtr()
	{}
	
	void bridge(const ptree& ptree, std::shared_ptr<TType>& to) override
	{
	    // read ptree["$type"] and call dynamic factory
	    std::string trueType = ptree.get("$type", TType::TypeName);
	    to = toolbox::Maker::instance().make<TType>(trueType);    
	    to->readPtree(ptree);
	}
	
	void bridge(const std::shared_ptr<TType>& from, ptree& ptree) override
	{
	    from->writePtree(ptree);
	}	
    };
    
    ///////////////////////////////////////////////////////////////////////////////////

    template <class TType>
    class BridgePtreeClass : public bridge::BridgeClass<toolbox::ptree::ptree, TType>,
			     public bridge::BridgeClass<TType, toolbox::ptree::ptree >
    {
    public: 
	BridgePtreeClass()
	{}
	
	void bridge(const toolbox::ptree::ptree& ptree, TType& to) override
	{
	    bridge::BridgeClass<toolbox::ptree::ptree, TType>::bridge(ptree, to);
	}
	
	void bridge(const TType& from, toolbox::ptree::ptree& ptree) override
	{
	    bridge::BridgeClass<TType, toolbox::ptree::ptree>::bridge(from, ptree);
	}
    };

    ///////////////////////////////////////////////////////////////////////////////////

    template <class T, class attributeType>
    class BridgePtreeAttribute : public bridge::Bridge<ptree, T>,
				 public bridge::Bridge<T, ptree>
    {
    public: 
      
	typedef std::function<attributeType& (T&)> AttributeAccessor;
	typedef std::function<const attributeType& (const T&)> ConstAttributeAccessor;
	
	BridgePtreeAttribute(const std::string& ptreeKey,
			      ConstAttributeAccessor reader, 
			      AttributeAccessor writer,
			      ValueType valueType = ValueType::E_Plain,
			      ContainerType containerType = ContainerType::E_Value)
		: m_ptreeKey(ptreeKey)
		, m_reader(reader)
		, m_writer(writer)
		, m_valueType(valueType)
		, m_containerType(containerType)
	{}
	
	void bridge(const toolbox::ptree::ptree& ptree, T& to) override
	{
	    boost::optional< const toolbox::ptree::ptree& > child = ptree.get_child_optional( m_ptreeKey );
	    if( !child )
	    {
		// TODO log missing element;
		return;
	    }
	    
	    toolbox::bridge::bridge(child.get(), m_writer(to));
	}
	
	void bridge(const T& from, toolbox::ptree::ptree& ptree) override
	{
	    toolbox::ptree::ptree::iterator newNodeIt = ptree.push_back( { m_ptreeKey, toolbox::ptree::ptree() } );
	    toolbox::ptree::ptree& child = newNodeIt->second;
	    toolbox::bridge::bridge(m_reader(from), child);
	}
	
	std::string m_ptreeKey;
 	ConstAttributeAccessor m_reader;
 	AttributeAccessor m_writer;
	ValueType m_valueType;
	ContainerType m_containerType;
    };

    ///////////////////////////////////////////////////////////////////////////////////

    template <class T, class attributeType>
    void* RegisterBridgePtreeAttribute(const std::string& key, 
				    std::function<const attributeType& (const T&)> constAccessor, 
				    std::function<      attributeType& (      T&)> accessor,
				    ValueType valueType = ValueType::E_Plain,
				    ContainerType containerType = ContainerType::E_Value)
    {
	    MDW_LOG_DEBUG("Attribute registration for " << key);
	    BridgePtreeAttribute<T, attributeType>* bridgeInstance = new BridgePtreeAttribute<T, attributeType>(key, constAccessor, accessor, valueType, containerType);
	    bridge::RegisterBridgeAttribute<T, ptree>(bridgeInstance);
	    bridge::RegisterBridgeAttribute<ptree, T>(bridgeInstance);
	    
	    return nullptr;
    }

}
}

#define BRIDGE_ATTRIBUTE_WITH_PTREE_2(Type, key, constAccessor, accessor) \
static void* TBX_COMPILATION_UNIQUE_ID = RegisterBridgePtreeAttribute<Type, std::string>(key, \
	[] (const Type& obj) -> decltype(obj.constAccessor()) { return obj.constAccessor; }, \
	[] (      Type& obj) -> decltype(obj.accessor())      { return obj.accessor; });

#define BRIDGE_MAKE_ATTRIBUTE_ACESSORS_2(Type, constAccessor, accessor) \
	[] (const Type& obj) -> decltype(obj.constAccessor) { return obj.constAccessor; },\
	[] (      Type& obj) -> decltype(obj.accessor) 	 { return obj.accessor; }

#define BRIDGE_MAKE_ATTRIBUTE_ACESSORS(Type, accessor) BRIDGE_MAKE_ATTRIBUTE_ACESSORS_2(Type, accessor, accessor) 
