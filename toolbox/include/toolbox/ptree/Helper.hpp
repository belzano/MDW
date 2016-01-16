#pragma once

#include "toolbox/Types.hpp"

#include "toolbox/bridge/Bridge.hpp"
#include "toolbox/ptree/Types.hpp"
#include "toolbox/ptree/Bridge.hpp"

namespace toolbox{
namespace ptree {
namespace helper {

	void WritePtree(const ptree& iNode, toolbox::DataPtr oData);

	void ReadPtree(/*const*/ toolbox::DataPtr iData, boost::property_tree::ptree& oNode);
	void ReadPtree(const std::string& filename, boost::property_tree::ptree& oNode);
	
	template <class T>
	void Bridge(/*const*/ toolbox::DataPtr iData, T& oObj)
	{
		boost::property_tree::ptree node;
		ReadPtree(iData, node);
		toolbox::bridge::bridge(node, oObj);
	}
	
	template <class T>
	void Bridge(const std::string& filename, T& oObj)
	{
		boost::property_tree::ptree node;
		ReadPtree(filename, node);
		toolbox::bridge::bridge(node, oObj);
	}
	

	template <class T>
	void RegisterPtreeClassPtr()
	{
	    // Assert there's not already a bridge registered
	    bridge::BridgeClass<ptree, std::shared_ptr<T> >::Instance() = new BridgePtreeClassPtr<T>();
	    bridge::BridgeClass<std::shared_ptr<T>, ptree >::Instance() = new BridgePtreeClassPtr<T>();
	}
	
	template <class T>
	void RegisterPtreeClass()
	{
	    // Assert there's not already a bridge registered
	    bridge::BridgeClass<ptree, T>::Instance() = new BridgePtreeClass<T>();
	    bridge::BridgeClass<T, ptree>::Instance() = new BridgePtreeClass<T>();
	}
}
}
}


