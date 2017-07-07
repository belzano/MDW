#pragma once

#include <set>
#include <vector>

#include "Node.hpp"
#include "Tools.hpp"

#include <iostream>
#include "Geometry.hpp"

//////////////////////////////////////////////////////////////////

class NodeGeoIndex
{
	public:
		void init(int hres, int vres, int count);
		
		void addToIndex( Node*);
		void removeFromIndex( Node*);
		
		void nearNodes(Node* node, int radius, const std::set<Node*>& excluded, std::set<Node*>& oSet);
		void nearNodes(Node* node1, Node* node2, int radius, std::set<Node*>& oSet);
		
		Node* nearestPointOnSameCell(const PointI& coord);
	
		void dump() const;
			
	private:
		int cellIndex(const Node* node);
		int cellIndex(const PointI& center);	
		int colIndex(const PointI& center);
		int rowIndex(const PointI& center);
		int cellIndex(int rowIdx, int colIdx);
		
		std::set<Node*>& cellAt(int rowIdx, int colIdx);
		std::set<Node*>& cellAt(int cellIdx);
		std::set<std::set<Node*>*> nodesAtCellRadiusRange(const PointI& node, int cellRadius);
		std::set<std::set<Node*>*> nodesAtSegmentRadiusRange(const PointI& node1,const PointI& node2, int cellRadius);
	

		int _cellSize;
		int _rowCount;
		int _colCount;
		std::vector< std::set< Node*> > _cells;
};

