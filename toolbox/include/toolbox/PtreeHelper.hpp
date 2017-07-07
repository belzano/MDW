#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <memory>
#include <functional>

#include "toolbox/Types.hpp"
#include "toolbox/Logger.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

///////////////////////////////////////////////
//   Parsing callbacks for types

template<class T>
void ptreeToObject(const boost::property_tree::ptree& iNode, T& oObject)
{
	oObject.toObject(iNode);
}

template<class T>
void objectToPtree(const T& iObject, boost::property_tree::ptree& oNode)
{
	iObject.toPtree(oNode);
}

///////////////////////////////////////////////

namespace toolbox
{
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	//   Base class for serializable documents
	
	class PtreeDocumentBase
	{		
	public:
	
		void toJson(DataPtr oData) const;
		void fromJson(DataPtr oData);
		void fromJson(const std::string& file);
		
		virtual void toObject(const boost::property_tree::ptree& node) = 0;
		virtual void toPtree(boost::property_tree::ptree& oNode) const = 0;
	};

	///////////////////////////////////////////////
	//  Per-type conversions
	
	template<class TDOC>
	class PtreeDocumentConversions
	{
		public:			
			typedef std::function<void (const TDOC&, boost::property_tree::ptree&)> ObjectToPtreeLambda;
			typedef std::function<void (const boost::property_tree::ptree&, TDOC&)> PtreeToObjectLambda;
			typedef std::map<std::string, ObjectToPtreeLambda > ObjectToPtreeLambdaMap;
			typedef std::map<std::string, PtreeToObjectLambda > PtreeToObjectLambdaMap;
			
			ObjectToPtreeLambdaMap _objectToPtreeLambdaMap;
			PtreeToObjectLambdaMap _ptreeToObjectLambdaMap;
	};	
	
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	
	template <class TDOC>		
	class PtreeDocument : public PtreeDocumentBase
	{		
	public:

		virtual void toObject(const boost::property_tree::ptree& node)
		{
			TDOC& oObject = *((TDOC*) this);
						
			const PtreeDocumentConversions<TDOC>& registry = GetPtreeDocumentRegistry();
			typename PtreeDocumentConversions<TDOC>::PtreeToObjectLambdaMap::const_iterator keyLambdaIt;
			for(keyLambdaIt  = registry._ptreeToObjectLambdaMap.begin();
				keyLambdaIt != registry._ptreeToObjectLambdaMap.end();
				++keyLambdaIt)
			{
				std::string key = keyLambdaIt->first;
			
				// Try get key in node
				boost::optional< const boost::property_tree::ptree& > child = node.get_child_optional( key );
				if( !child )
				{   // child node is missing
					MDW_LOG_DEBUG("Unset tag in Document ["<< key << "]");	
					continue;
				}
				
				keyLambdaIt->second(child.get(), oObject);
			}			
		}

		virtual void toPtree(boost::property_tree::ptree& oNode) const
		{
			const TDOC& ioObject = *(TDOC*)this;
			
			const PtreeDocumentConversions<TDOC>& registry = GetPtreeDocumentRegistry();
			typename PtreeDocumentConversions<TDOC>::ObjectToPtreeLambdaMap::const_iterator keyLambdaIt;
			
			for(keyLambdaIt  = registry._objectToPtreeLambdaMap.begin();
				keyLambdaIt != registry._objectToPtreeLambdaMap.end();
				++keyLambdaIt)
			{
				std::string key = keyLambdaIt->first;
				boost::property_tree::ptree::iterator newNodeIt = oNode.push_back( { key, boost::property_tree::ptree() } );					
				boost::property_tree::ptree& newNode = newNodeIt->second;
				keyLambdaIt->second(ioObject, newNode);
			}			
		}	
	
		// This one must always be defined in the TDOC class and never been instanciated here
		template <class K>
		static void registerConversions(PtreeDocumentConversions<K>&)
		{
			// TODO static_assert ??
			MDW_LOG_ERROR("You must define registerConversions in TDOC class.");
		}
	
	protected:
					
		static const PtreeDocumentConversions<TDOC>& GetPtreeDocumentRegistry()
		{
			static PtreeDocumentConversions<TDOC> conversions;
			static bool init = false;
			if (!init)
			{
				TDOC::registerConversions(conversions);
				init = true;
			}
			return conversions;
		}
	};
	
}  // namespace toolbox end	
		
///////////////////////////////////////////////
////////////////////////////////////////////////
// Specializations for base types
template<> void ptreeToObject<U8>				(const boost::property_tree::ptree& iNode, U8& oResult);
template<> void ptreeToObject<S8>				(const boost::property_tree::ptree& iNode, S8& oResult);
template<> void ptreeToObject<U16>				(const boost::property_tree::ptree& iNode, U16& oResult);
template<> void ptreeToObject<S16>				(const boost::property_tree::ptree& iNode, S16& oResult);
template<> void ptreeToObject<U32>				(const boost::property_tree::ptree& iNode, U32& oResult);
template<> void ptreeToObject<S32>				(const boost::property_tree::ptree& iNode, S32& oResult);
template<> void ptreeToObject<U64>				(const boost::property_tree::ptree& iNode, U64& oResult);
template<> void ptreeToObject<S64>				(const boost::property_tree::ptree& iNode, S64& oResult);
template<> void ptreeToObject<std::string> 		(const boost::property_tree::ptree& iNode, std::string& oResult);
template<> void ptreeToObject<toolbox::DataPtr>	(const boost::property_tree::ptree& iNode, toolbox::DataPtr& oResult);

template<> void objectToPtree<U8>				(const U8& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<S8>				(const S8& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<U16>				(const U16& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<S16>				(const S16& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<U32>				(const U32& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<S32>				(const S32& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<U64>				(const U64& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<S64>				(const S64& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<std::string> 		(const std::string& oResult, boost::property_tree::ptree& iNode);
template<> void objectToPtree<toolbox::DataPtr>	(const toolbox::DataPtr& oResult, boost::property_tree::ptree& iNode);

////////////////////////////////////////////////
// Specializations for stl containers

// list
template<class K> void ptreeToObjectList	(const boost::property_tree::ptree& iNode, std::list<K>& oResult)
{
	BOOST_FOREACH (const boost::property_tree::ptree::value_type& itemPair, iNode) 
	{
		K object;
		ptreeToObject(itemPair.second, object);
		oResult.push_back(object);
    }	
}

template<class K> void objectListToPtree	(const std::list<K>& oResult, boost::property_tree::ptree& iNode)
{
	typename std::list<K>::const_iterator it;
	for(it  = oResult.begin(); it != oResult.end();	++it)
	{
		boost::property_tree::ptree child;
		objectToPtree<K>(*it, child);
		iNode.push_back(std::make_pair("", child));
	}
}

// vector
template<class K> void ptreeToObjectVector	(const boost::property_tree::ptree& iNode, std::vector<K>& oResult)
{
	BOOST_FOREACH (const boost::property_tree::ptree::value_type& itemPair, iNode) 
	{
		K object;
		ptreeToObject(itemPair.second, object);
		oResult.push_back(object);
    }	
}

template<class K> void objectVectorToPtree	(const std::vector<K>& oResult, boost::property_tree::ptree& iNode)
{
	typename std::vector<K>::const_iterator it;
	for(it  = oResult.begin(); it != oResult.end();	++it)
	{
		boost::property_tree::ptree child;
		objectToPtree<K>(*it, child);
		iNode.push_back(std::make_pair("", child));
	}
}

// set
template<class K> void ptreeToObjectSet		(const boost::property_tree::ptree& iNode, std::set<K>& oResult)
{
	BOOST_FOREACH (const boost::property_tree::ptree::value_type& itemPair, iNode) 
	{
		K object;
		ptreeToObject(itemPair.second, object);
		oResult.insert(object);
    }	
}

template<class K> void objectSetToPtree		(const std::set<K>& oResult, boost::property_tree::ptree& iNode)
{
	typename std::set<K>::const_iterator it;
	for(it  = oResult.begin(); it != oResult.end();	++it)
	{
		boost::property_tree::ptree child;
		objectToPtree<K>(*it, child);
		iNode.push_back(std::make_pair("", child));
	}
}

// map
template<class K, class V> void ptreeToObjectMap	(const boost::property_tree::ptree& /*iNode*/, std::map<K, V>& /*oResult*/)
{
/*	BOOST_FOREACH (const boost::property_tree::ptree::value_type& itemPair, iNode) 
	{
		K object;
		V value;
		ptreeToObject(itemPair.first, object);
		ptreeToObject(itemPair.second, value);
		oResult.insert({object, value});
    }	
*/
}

template<class K, class V> void objectMapToPtree	(const std::map<K, V>& /*oResult*/, boost::property_tree::ptree& /*iNode*/)
{
	/*
	typename std::map<K, V>::const_iterator it;
	for(it  = oResult.begin(); it != oResult.end();	++it)
	{
		boost::property_tree::ptree child;
		objectToPtree<K>(*it, child);
		iNode.push_back(std::make_pair("", child));
	}
	*/
}

#define MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(container, type)														\
template<> void ptreeToObject<container<type> >	(const boost::property_tree::ptree& iNode, container<type>& oResult);	\
template<> void objectToPtree<container<type> >	(const container<type>& oResult, boost::property_tree::ptree& iNode);

#define MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1(container, type, toCbk, fromCbk)										\
template<> void ptreeToObject<container<type> >	(const boost::property_tree::ptree& iNode, container<type>& oResult) 	\
{ return toCbk(iNode, oResult); }																						\
template<> void objectToPtree<container<type> >	(const container<type>& oResult, boost::property_tree::ptree& iNode)	\
{ return fromCbk(oResult, iNode); }


#define MME_DECLARE_PTREE_SERIALIZER_LIST(type) MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(std::list, type)
#define MME_DEFINE_PTREE_SERIALIZER_LIST( type) MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1( std::list, type, ptreeToObjectList, objectListToPtree)

#define MME_DECLARE_PTREE_SERIALIZER_SET(type) MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(std::set, type)
#define MME_DEFINE_PTREE_SERIALIZER_SET( type) MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1( std::set, type, ptreeToObjectSet, objectSetToPtree)

#define MME_DECLARE_PTREE_SERIALIZER_VECTOR(type) MME_DECLARE_PTREE_SERIALIZER_CONTAINER_1(std::vector, type)
#define MME_DEFINE_PTREE_SERIALIZER_VECTOR( type) MME_DEFINE_PTREE_SERIALIZER_CONTAINER_1( std::vector, type, ptreeToObjectVector, objectVectorToPtree)


MME_DECLARE_PTREE_SERIALIZER_LIST(std::string) 
MME_DECLARE_PTREE_SERIALIZER_SET(std::string) 
MME_DECLARE_PTREE_SERIALIZER_VECTOR(std::string)


/*
///////////////////////////////////////////////
//   Test
		
class DocumentTest : public toolbox::PtreeDocument<DocumentTest>
{
	template <class K>
	static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
	{
		MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, int, x)
		MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, text)
	}
	
	MME_REGISTER_ATTRIBUTE(int, x)
	MME_REGISTER_ATTRIBUTE(std::string, text)
};

// Test class aggregation		
class DocumentTest2 : public toolbox::PtreeDocument<DocumentTest2>
{
	template <class K>
	static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
	{
		MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, DocumentTest, x)
		MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, text)
	}
	
	MME_REGISTER_ATTRIBUTE( DocumentTest, x)
	MME_REGISTER_ATTRIBUTE( std::string, text)
};

// Test class inheritance
class DocumentTest3 : public DocumentTest2, public toolbox::PtreeDocument<DocumentTest3>
{
	template <class K>
	static void registerConversions(toolbox::PtreeDocumentConversions<K>& registry)
	{
		DocumentTest2::registerConversions<K>(registry);
		
		MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, int, b)
		MME_REGISTER_ATTRIBUTE_TO_PTREE(K, registry, std::string, textre)
	}
	
	MME_REGISTER_ATTRIBUTE( int, b)
	MME_REGISTER_ATTRIBUTE( std::string, textre)
};

////////////////////////////////////////////////
	
*/



