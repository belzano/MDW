#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>

#include "toolbox/Types.hpp"
#include "toolbox/entity/Entity.hpp"
#include "toolbox/entity/Factory.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/Typename.hpp"

#include "toolbox/ptree/Types.hpp"

#include <boost/foreach.hpp>

///////////////////////////////////////////////
////////////////////////////////////////////////
// Specializations for base types
using toolbox::ptree::Node;

void convert(const Node& iNode, U8& oResult);
void convert(const Node& iNode, S8& oResult);
void convert(const Node& iNode, U16& oResult);
void convert(const Node& iNode, S16& oResult);
void convert(const Node& iNode, U32& oResult);
void convert(const Node& iNode, S32& oResult);
void convert(const Node& iNode, U64& oResult);
void convert(const Node& iNode, S64& oResult);

void convert(const U8& oResult, Node& iNode);
void convert(const S8& oResult, Node& iNode);
void convert(const U16& oResult, Node& iNode);
void convert(const S16& oResult, Node& iNode);
void convert(const U32& oResult, Node& iNode);
void convert(const S32& oResult, Node& iNode);
void convert(const U64& oResult, Node& iNode);
void convert(const S64& oResult, Node& iNode);

void convert(const Node& iNode, std::string& oResult);
void convert(const std::string& oResult, Node& iNode);

void convert(const Node& iNode, toolbox::DataPtr& oResult);
void convert(const toolbox::DataPtr& oResult, Node& iNode);

void convert(const toolbox::ptree::PtreeEntity& iEntity, Node& oNode);
void convert(const Node& iNode, toolbox::ptree::PtreeEntity& oEntity);

////////////////////////////////////////////////

#define MDW_PTREE_CONVERSION_SHARED_DECLARE(K)							\
void convert(const Node& iNode, std::shared_ptr<K>& to);

#define MDW_PTREE_CONVERSION_SHARED_DEFINE(K)							\
void convert(const Node& iNode, std::shared_ptr<K>& to)				\
{																		\
	std::string trueType = iNode.get("$type", type_name<K>());			\
	to = toolbox::entity::Factory::instance().make<K>(trueType);		\
	if (to.get())														\
	  convert(iNode, *to.get());										\
}																		\
void convert(const std::shared_ptr<K>& from, Node& oNode)				\
{																		\
	/* TODO write iNode["$type"]*/										\
	if (from.get())														\
	  convert(*from.get(), oNode);										\
}																		\

////////////////////////////////////////////////

#define MDW_PTREE_CONVERSION_CONTAINER_1_DECLARE(container, K)       	\
void convert(const Node& iNode, container< K >& oResult);				\
void convert(const container< K >& oResult, Node& iNode);

#define MDW_PTREE_CONVERSION_CONTAINER_1_DEFINE(container, K)       	\
void convert(const Node& iNode, container<K>& oResult)					\
{																		\
	BOOST_FOREACH (const Node::value_type& itemPair, iNode) 			\
	{																	\
		K object;														\
		convert(itemPair.second, object);								\
		oResult.push_back(object);										\
	}																	\
}																		\
void convert(const container<K>& oResult, Node& iNode)					\
{																		\
	typename container<K>::const_iterator it;							\
	for(it  = oResult.begin(); it != oResult.end();	++it)				\
	{																	\
		Node child;													\
		convert(*it, child);											\
		iNode.push_back(std::make_pair("", child));						\
	}																	\
}																		\

#define MDW_PTREE_CONVERSION_OBJECT_DECLARE(K)							\
MDW_PTREE_CONVERSION_CONTAINER_1_DECLARE(std::list, K)       			\
MDW_PTREE_CONVERSION_CONTAINER_1_DECLARE(std::vector, K)

#define MDW_PTREE_CONVERSION_OBJECT_DEFINE(K)					\
MDW_PTREE_CONVERSION_CONTAINER_1_DEFINE(std::list, K)       	\
MDW_PTREE_CONVERSION_CONTAINER_1_DEFINE(std::vector, K) 

MDW_PTREE_CONVERSION_OBJECT_DECLARE(U32)
MDW_PTREE_CONVERSION_OBJECT_DECLARE(S32)
MDW_PTREE_CONVERSION_OBJECT_DECLARE(std::string)


#define MDW_PTREE_CONVERSION_ENTITY_DECLARE(type)	\
MDW_PTREE_CONVERSION_SHARED_DECLARE(type)			\
MDW_PTREE_CONVERSION_OBJECT_DECLARE(type)			\
MDW_PTREE_CONVERSION_OBJECT_DECLARE(std::shared_ptr<type>)

#define MDW_PTREE_CONVERSION_ENTITY_DEFINE(type)	\
MDW_PTREE_CONVERSION_SHARED_DEFINE(type)			\
MDW_PTREE_CONVERSION_OBJECT_DEFINE(type)			\
MDW_PTREE_CONVERSION_OBJECT_DEFINE(std::shared_ptr<type>)

MDW_PTREE_CONVERSION_ENTITY_DECLARE(toolbox::ptree::PtreeEntity)

////////////////////////////////////////////////

#define MDW_PTREE_CONVERSION_CONTAINER_2_DECLARE(container, K, V)	\
void convert(const Node& iNode, container<K, V>& oResult);			\
void convert(const container<K, V>& oResult, Node& iNode);

#define MDW_PTREE_CONVERSION_CONTAINER_2_DEFINE(container, K, V, cbk)	\
void convert(const Node& iNode, container<K, V>& oResult)  			\
{ return cbk<K, V>(iNode, oResult); }									\
void convert(const container<K, V>& oResult, Node& iNode)				\
{ return cbk<K, V>(oResult, iNode); }


#define MDW_PTREE_CONVERSION_MAP_DECLARE(K, V) MDW_PTREE_CONVERSION_CONTAINER_2_DECLARE(std::map, K, V)
#define MDW_PTREE_CONVERSION_MAP_DEFINE(K, V) MDW_PTREE_CONVERSION_CONTAINER_2_DEFINE( std::map, K, V, toolbox::ptree::convertMap)





namespace toolbox {
namespace ptree {
	////////////////////////////////////////////////

	// set
	template<class K> void 
	convertSet(const Node& iNode, std::set<K>& oResult)
	{
		BOOST_FOREACH (const Node::value_type& itemPair, iNode) 
		{
			K object;
			convert(itemPair.second, object);
			oResult.insert(object);
		}
	}

	template<class K> void 
	convertSet(const std::set<K>& oResult, Node& iNode)
	{
		typename std::set<K>::const_iterator it;
		for(it  = oResult.begin(); it != oResult.end();	++it)
		{
			Node child;
			convert(*it, child);
			iNode.push_back(std::make_pair("", child));
		}
	}

	////////////////////////////////////////////////

	template<class K, class V> 
	void convertMap(const Node& iNode, std::map<K, V>& oResult)
	{
		BOOST_FOREACH (const Node::value_type& itemPair, iNode) 
		{
			K object;
			V value;
			convert(itemPair.first, object);
			convert(itemPair.second, value);
			oResult.insert({object, value});
		}	

	}

	template<class K, class V> 
	void convertMap(const std::map<K, V>& from, Node& iNode)
	{
		typename std::map<K, V>::const_iterator it;
		for(it  = from.begin(); it != from.end();	++it)
		{
			Node child;
			convert(it->second, child);
			iNode.push_back(std::make_pair(it->first, child));
		}
	}

}
}
