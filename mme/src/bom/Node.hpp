#pragma once

#include <list>
#include <set>
#include <vector>

#include "Segment.hpp"
#include "Tools.hpp"

#include <iostream>
#include "Geometry.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////

class Node
{
	public:

	Node(int rowIdx, int colIdx): _weight(1) 
	{
		_center[0] = rowIdx;
		_center[1] = colIdx;
		
		if (_center[0] < 0) throw;
		if (_center[1] < 0) throw;
	}
	//Node(PointI& iCenter): _center(iCenter) {}
	Node(PointI iCenter): _center(iCenter), _weight(1) 
	{
		if (iCenter[0] < 0) throw;
		if (iCenter[1] < 0) throw;
	}
	Node(PointF iCenter): _center(iCenter), _weight(1) 
	{
		if (iCenter[0] < 0) throw;
		if (iCenter[1] < 0) throw;
	}
		
	static Node* createNewAsBarycentre(const std::set<Node*>& iNodes);	

	PointF center_f() const { return _center;}
	PointI center_i() const { return _center;}
	
	const PointF& center() const { return _center;}
		  PointF& center()       { return _center;}
	
	float distance(const Node* iOther) const
	{
		return Tools::distance(_center, iOther->_center);
	}
	
	std::ostream& toStream(std::ostream& ioStream);
	
	private:
	
		PointF 			_center;
		int 			_color;
		int 			_weight;
	
};

//////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& ioStream, Node& iSegment);

//////////////////////////////////////////////////////////////////


