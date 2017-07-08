#pragma once

#include <iostream>
#include <memory>
#include <list>
#include <set>

#include "toolbox/Types.hpp"
#include "uhf/kvs/component/KeyValueStorage.hpp"
#include "Parameters.hpp"

#include "Geometry.hpp"


using namespace std;
 
class ConnectedSet;
class ConnectedSetStats;
class Node;

class QueryContext
{
	typedef uhf::kvs::component::KeyValueStoragePtr KeyValueStoragePtr;

public:
 
	QueryContext();
	~QueryContext();
	
	bool init ( toolbox::DataPtr iData, 
				KeyValueStoragePtr iCell);
		
	void log(const PointMatrix& iImg);
	void log(const std::set<Node*>& iGraph);
	void log(const ConnectedSet& iGraph);
	void log(const ConnectedSetStats& iStats);
	void log(const std::list<ConnectedSet>& iSets);
	void log(const ConnectedSet& iGraph, const ConnectedSetStats& iStats);
	
	const PointMatrix& getSourceImage() const {return _srcImg;}
		
	const Parameters& getParameters() const {return _parameters;}

private:
	
	KeyValueStoragePtr _storageCell;
	PointMatrix	_srcImg;
	
	// Process state tracking
	int _stepIdx;
	
	// Parameters for procesing
	Parameters _parameters;
	
	void draw(const ConnectedSet& iGraph, PointMatrix& iImg);
	void draw(const ConnectedSetStats& iGraph, PointMatrix& iImg);
};

