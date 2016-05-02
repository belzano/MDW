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
//#include "toolbox/ptree/Conversions.hpp"

#include <boost/foreach.hpp>


namespace toolbox {
namespace bridge {

///////////////////////////////////////////////
////////////////////////////////////////////////
// Specializations for base types
  using toolbox::ptree::Node;

template<> void bridge<Node, U8>			(const Node& iNode, U8& oResult);
template<> void bridge<Node, S8>			(const Node& iNode, S8& oResult);
template<> void bridge<Node, U16>			(const Node& iNode, U16& oResult);
template<> void bridge<Node, S16>			(const Node& iNode, S16& oResult);
template<> void bridge<Node, U32>			(const Node& iNode, U32& oResult);
template<> void bridge<Node, S32>			(const Node& iNode, S32& oResult);
template<> void bridge<Node, U64>			(const Node& iNode, U64& oResult);
template<> void bridge<Node, S64>			(const Node& iNode, S64& oResult);
template<> void bridge<Node, std::string> 		(const Node& iNode, std::string& oResult);
template<> void bridge<Node, toolbox::DataPtr>		(const Node& iNode, toolbox::DataPtr& oResult);

template<> void bridge<U8, Node>			(const U8& oResult, Node& iNode);
template<> void bridge<S8, Node>			(const S8& oResult, Node& iNode);
template<> void bridge<U16, Node>			(const U16& oResult, Node& iNode);
template<> void bridge<S16, Node>			(const S16& oResult, Node& iNode);
template<> void bridge<U32, Node>			(const U32& oResult, Node& iNode);
template<> void bridge<S32, Node>			(const S32& oResult, Node& iNode);
template<> void bridge<U64, Node>			(const U64& oResult, Node& iNode);
template<> void bridge<S64, Node>			(const S64& oResult, Node& iNode);
template<> void bridge<std::string, Node> 		(const std::string& oResult, Node& iNode);
template<> void bridge<toolbox::DataPtr, Node>		(const toolbox::DataPtr& oResult, Node& iNode);

////////////////////////////////////////////////
// Specializations for stl containers
////////////////////////////////////////////////

// Shared ptr
template<class K> 
void bridgePtr(const Node& iNode, std::shared_ptr<K>& to)
{
	convert(iNode, to);
}

template<class K> 
void bridgePtr(const std::shared_ptr<K>& from, Node& oNode)
{
	convert(from, oNode);
}

////////////////////////////////////////////////

// list
template<class K> 
void bridgeList(const Node& iNode, std::list<K>& oResult)
{
    BOOST_FOREACH (const Node::value_type& itemPair, iNode) 
    {
	K object;
	bridge(itemPair.second, object);
	oResult.push_back(object);
    }	
}

template<class K> 
void bridgeList(const std::list<K>& oResult, Node& iNode)
{
    typename std::list<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	Node child;
	bridge<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}

// ptr list
template<class K> 
void bridgePtrList(const Node& iNode, std::list<std::shared_ptr<K>>& oResult)
{
    BOOST_FOREACH (const Node::value_type& itemPair, iNode) 
    {
	std::shared_ptr<K> object;
	bridgePtr<K>(itemPair.second, object);
	oResult.push_back(object);
    }	
}

template<class K> 
void bridgePtrList(const std::list<std::shared_ptr<K> >& oResult, Node& iNode)
{
    typename std::list<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	Node child;
	bridgePtr<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}


////////////////////////////////////////////////

// vector
template<class K> 
void bridgeVector(const Node& iNode, std::vector<K>& oResult)
{
    BOOST_FOREACH (const Node::value_type& itemPair, iNode) 
    {
	K object;
	bridge(itemPair.second, object);
	oResult.push_back(object);
    }	
}

template<class K> 
void bridgeVector(const std::vector<K>& oResult, Node& iNode)
{
    typename std::vector<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	Node child;
	bridge<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}

////////////////////////////////////////////////

// set
template<class K> void 
bridgeSet(const Node& iNode, std::set<K>& oResult)
{
    BOOST_FOREACH (const Node::value_type& itemPair, iNode) 
    {
	K object;
	bridge(itemPair.second, object);
	oResult.insert(object);
    }	
}

template<class K> void 
bridgeSet(const std::set<K>& oResult, Node& iNode)
{
    typename std::set<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	Node child;
	bridge<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}

////////////////////////////////////////////////

// map
template<class K, class V> 
void bridgeMap(const Node& iNode, std::map<K, V>& oResult)
{
    BOOST_FOREACH (const Node::value_type& itemPair, iNode) 
    {
	K object;
	V value;
	bridge(itemPair.first, object);
	bridge(itemPair.second, value);
	oResult.insert({object, value});
    }	

}

template<class K, class V> 
void bridgeMap(const std::map<K, V>& from, Node& iNode)
{
    typename std::map<K, V>::const_iterator it;
    for(it  = from.begin(); it != from.end();	++it)
    {
	Node child;
	bridge<K>(it->second, child);
	iNode.push_back(std::make_pair(it->first, child));
    }
}

////////////////////////////////////////////////

#define MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(container, type)														\
template<> void bridge<Node, container<type> >	(const Node& iNode, container<type>& oResult);	\
template<> void bridge<container<type>, Node >	(const container<type>& oResult, Node& iNode);

#define MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1(container, type, cbk)										\
template<> void bridge<Node, container<type> >	(const Node& iNode, container<type>& oResult) 	\
{ return cbk<type>(iNode, oResult); }																						\
template<> void bridge<container<type>, Node >	(const container<type>& oResult, Node& iNode)	\
{ return cbk<type>(oResult, iNode); }


#define MME_DECLARE_PTREE_SERIALIZER_LIST(type) MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(std::list, type)
#define MME_DEFINE_PTREE_SERIALIZER_LIST( type) MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1( std::list, type, bridgeList)

#define MME_DECLARE_PTREE_SERIALIZER_SET(type) MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(std::set, type)
#define MME_DEFINE_PTREE_SERIALIZER_SET( type) MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1( std::set, type, bridgeSet)

#define MME_DECLARE_PTREE_SERIALIZER_VECTOR(type) MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(std::vector, type)
#define MME_DEFINE_PTREE_SERIALIZER_VECTOR( type) MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1( std::vector, type, bridgeVector)


MME_DECLARE_PTREE_SERIALIZER_LIST(std::string) 
MME_DECLARE_PTREE_SERIALIZER_SET(std::string) 
MME_DECLARE_PTREE_SERIALIZER_VECTOR(std::string)

MME_DECLARE_PTREE_SERIALIZER_LIST(U32) 
MME_DECLARE_PTREE_SERIALIZER_SET(U32) 
MME_DECLARE_PTREE_SERIALIZER_VECTOR(U32)

MME_DECLARE_PTREE_SERIALIZER_LIST(S32) 
MME_DECLARE_PTREE_SERIALIZER_SET(S32) 
MME_DECLARE_PTREE_SERIALIZER_VECTOR(S32)
}
}





