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

#include <boost/foreach.hpp>


namespace toolbox {
namespace bridge {

///////////////////////////////////////////////
////////////////////////////////////////////////
// Specializations for base types
  using toolbox::ptree::ptree;

template<> void bridge<ptree, U8>			(const ptree& iNode, U8& oResult);
template<> void bridge<ptree, S8>			(const ptree& iNode, S8& oResult);
template<> void bridge<ptree, U16>			(const ptree& iNode, U16& oResult);
template<> void bridge<ptree, S16>			(const ptree& iNode, S16& oResult);
template<> void bridge<ptree, U32>			(const ptree& iNode, U32& oResult);
template<> void bridge<ptree, S32>			(const ptree& iNode, S32& oResult);
template<> void bridge<ptree, U64>			(const ptree& iNode, U64& oResult);
template<> void bridge<ptree, S64>			(const ptree& iNode, S64& oResult);
template<> void bridge<ptree, std::string> 		(const ptree& iNode, std::string& oResult);
template<> void bridge<ptree, toolbox::DataPtr>		(const ptree& iNode, toolbox::DataPtr& oResult);

template<> void bridge<U8, ptree>			(const U8& oResult, ptree& iNode);
template<> void bridge<S8, ptree>			(const S8& oResult, ptree& iNode);
template<> void bridge<U16, ptree>			(const U16& oResult, ptree& iNode);
template<> void bridge<S16, ptree>			(const S16& oResult, ptree& iNode);
template<> void bridge<U32, ptree>			(const U32& oResult, ptree& iNode);
template<> void bridge<S32, ptree>			(const S32& oResult, ptree& iNode);
template<> void bridge<U64, ptree>			(const U64& oResult, ptree& iNode);
template<> void bridge<S64, ptree>			(const S64& oResult, ptree& iNode);
template<> void bridge<std::string, ptree> 		(const std::string& oResult, ptree& iNode);
template<> void bridge<toolbox::DataPtr, ptree>		(const toolbox::DataPtr& oResult, ptree& iNode);

////////////////////////////////////////////////
// Specializations for stl containers
////////////////////////////////////////////////

// Shared ptr
template<class K> 
void bridgePtr(const ptree& iNode, std::shared_ptr<K>& to)
{
    // read iNode["$type"] and call dynamic factory
    std::string trueType = iNode.get("$type", K::TypeName);
    to = toolbox::Maker::instance().make<K>(trueType);
    if (to.get())
      bridge(iNode, *to.get());
}

template<class K> 
void bridgePtr(const std::shared_ptr<K>& from, ptree& oNode)
{
    // TODO write iNode["$type"]
    if (from.get())
      bridge(*from.get(), oNode);
}

////////////////////////////////////////////////

// list
template<class K> 
void bridgeList(const ptree& iNode, std::list<K>& oResult)
{
    BOOST_FOREACH (const ptree::value_type& itemPair, iNode) 
    {
	K object;
	bridge(itemPair.second, object);
	oResult.push_back(object);
    }	
}

template<class K> 
void bridgeList(const std::list<K>& oResult, ptree& iNode)
{
    typename std::list<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	ptree child;
	bridge<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}

// ptr list
template<class K> 
void bridgePtrList(const ptree& iNode, std::list<std::shared_ptr<K>>& oResult)
{
    BOOST_FOREACH (const ptree::value_type& itemPair, iNode) 
    {
	std::shared_ptr<K> object;
	bridgePtr<K>(itemPair.second, object);
	oResult.push_back(object);
    }	
}

template<class K> 
void bridgePtrList(const std::list<std::shared_ptr<K> >& oResult, ptree& iNode)
{
    typename std::list<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	ptree child;
	bridgePtr<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}


////////////////////////////////////////////////

// vector
template<class K> 
void bridgeVector(const ptree& iNode, std::vector<K>& oResult)
{
    BOOST_FOREACH (const ptree::value_type& itemPair, iNode) 
    {
	K object;
	bridge(itemPair.second, object);
	oResult.push_back(object);
    }	
}

template<class K> 
void bridgeVector(const std::vector<K>& oResult, ptree& iNode)
{
    typename std::vector<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	ptree child;
	bridge<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}

////////////////////////////////////////////////

// set
template<class K> void 
bridgeSet(const ptree& iNode, std::set<K>& oResult)
{
    BOOST_FOREACH (const ptree::value_type& itemPair, iNode) 
    {
	K object;
	bridge(itemPair.second, object);
	oResult.insert(object);
    }	
}

template<class K> void 
bridgeSet(const std::set<K>& oResult, ptree& iNode)
{
    typename std::set<K>::const_iterator it;
    for(it  = oResult.begin(); it != oResult.end();	++it)
    {
	ptree child;
	bridge<K>(*it, child);
	iNode.push_back(std::make_pair("", child));
    }
}

////////////////////////////////////////////////

// map
template<class K, class V> 
void bridgeMap(const ptree& iNode, std::map<K, V>& oResult)
{
    BOOST_FOREACH (const ptree::value_type& itemPair, iNode) 
    {
	K object;
	V value;
	bridge(itemPair.first, object);
	bridge(itemPair.second, value);
	oResult.insert({object, value});
    }	

}

template<class K, class V> 
void bridgeMap(const std::map<K, V>& from, ptree& iNode)
{
    typename std::map<K, V>::const_iterator it;
    for(it  = from.begin(); it != from.end();	++it)
    {
	ptree child;
	bridge<K>(it->second, child);
	iNode.push_back(std::make_pair(it->first, child));
    }
}

////////////////////////////////////////////////

#define MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(container, type)														\
template<> void bridge<ptree, container<type> >	(const ptree& iNode, container<type>& oResult);	\
template<> void bridge<container<type>, ptree >	(const container<type>& oResult, ptree& iNode);

#define MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1(container, type, cbk)										\
template<> void bridge<ptree, container<type> >	(const ptree& iNode, container<type>& oResult) 	\
{ return cbk<type>(iNode, oResult); }																						\
template<> void bridge<container<type>, ptree >	(const container<type>& oResult, ptree& iNode)	\
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





