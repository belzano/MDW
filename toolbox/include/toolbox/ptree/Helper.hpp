#pragma once

#include "toolbox/Types.hpp"
#include "toolbox/ptree/Types.hpp"

#include <string>
#include <set>

namespace toolbox{
namespace ptree {

namespace helper {

	void WritePtree(const Node& iNode, toolbox::DataPtr oData);

	void ReadPtree(/*const*/ toolbox::DataPtr iData, Node& oNode);
	void ReadPtree(const std::string& filename, Node& oNode);

	void DistinctTagValues(const std::string tag, const Node& oNode, std::set<std::string>& result);
}
	
	template <class T>
	void bridge(const std::string iKey, const Node& ptree, T& to)
	{
	    boost::optional< const Node& > nodeIt = ptree.get_child_optional( iKey );
	    if( !nodeIt )
	    {
			// TODO log missing element? Set default?
			return;
	    }
	    const Node& child = nodeIt.get();
	    convert(child, to);
	}
	
	template <class T>
	void bridge(const std::string iKey, const T& from, Node& ptree)
	{
	    Node::iterator newNodeIt = ptree.push_back( { iKey, Node() } );
	    Node& child = newNodeIt->second;
	    convert(from, child);
	}
	
	template <class T>
	void fromJsonFile(const std::string& filename, T& oObj)
	{
		Node node;
		helper::ReadPtree(filename, node);
		convert(node, oObj);
	}
	
	template <class T>
	void fromJsonData(/*const*/ toolbox::DataPtr iData, T& oObj)
	{
		Node node;
		helper::ReadPtree(iData, node);
		convert(node, oObj);
	}
		
}
}


