#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>

#include "toolbox/Types.hpp"
#include "toolbox/Logger.hpp"

#include "toolbox/bridge/Bridge.hpp"
#include "toolbox/ptree/Types.hpp"
#include "PtreeSpecializations.hpp"
//#include "toolbox/ptree/Conversions.hpp"

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
    class BridgePtreeClassPtr : public bridge::BridgeClass<Node, std::shared_ptr<TType> >,
				public bridge::BridgeClass<std::shared_ptr<TType>, Node >
    {
    public: 
	BridgePtreeClassPtr()
	{}
	
	void bridge(const Node& , std::shared_ptr<TType>& ) override
	{
	    //convert(Node, to);
	}
	
	void bridge(const std::shared_ptr<TType>& , Node& ) override
	{
		//convert(from, Node);
	}	
    };
    
    ///////////////////////////////////////////////////////////////////////////////////

    template <class TType>
    class BridgePtreeClass : public bridge::BridgeClass<toolbox::ptree::Node, TType>,
			     public bridge::BridgeClass<TType, toolbox::ptree::Node >
    {
    public: 
	BridgePtreeClass()
	{}
	
	void bridge(const toolbox::ptree::Node& ptree, TType& to) override
	{
	    bridge::BridgeClass<toolbox::ptree::Node, TType>::bridge(ptree, to);
	}
	
	void bridge(const TType& from, toolbox::ptree::Node& ptree) override
	{
	    bridge::BridgeClass<TType, toolbox::ptree::Node>::bridge(from, ptree);
	}
    };

    ///////////////////////////////////////////////////////////////////////////////////

    template <class T, class attributeType>
    class BridgePtreeAttribute : public bridge::Bridge<Node, T>,
				 public bridge::Bridge<T, Node>
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
	
	void bridge(const toolbox::ptree::Node& ptree, T& to) override
	{
	    boost::optional< const toolbox::ptree::Node& > child = ptree.get_child_optional( m_ptreeKey );
	    if( !child )
	    {
		// TODO log missing element;
		return;
	    }
	    
	    toolbox::bridge::bridge(child.get(), m_writer(to));
	}
	
	void bridge(const T& from, toolbox::ptree::Node& ptree) override
	{
	    toolbox::ptree::Node::iterator newNodeIt = ptree.push_back( { m_ptreeKey, toolbox::ptree::Node() } );
	    toolbox::ptree::Node& child = newNodeIt->second;
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
	    bridge::RegisterBridgeAttribute<T, Node>(bridgeInstance);
	    bridge::RegisterBridgeAttribute<Node, T>(bridgeInstance);
	    
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
