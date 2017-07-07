#include "NodeGeoIndex.hpp"
#include "toolbox/Logger.hpp"

#include <iostream>

#include "Geometry.hpp"

using namespace std;

void NodeGeoIndex::init(int hres, int vres, int count)
{
	const int wishedPointCountPerCell = 5;
	
	if (count == 0)
	{
		_cellSize = std::max(hres, vres);
		
	}
	else
	{	
		// Lets try to get 10 points per cell	
		float avgPointsPerSqPx = count * 1.0 / (hres * vres);
		_cellSize = (int) sqrtf(wishedPointCountPerCell / avgPointsPerSqPx); 
	}

	_colCount = 1 + (int) (hres * 1.0 / _cellSize);
	_rowCount = 1 + (int) (vres * 1.0 / _cellSize);
	
	MDW_LOG_DEBUG("GeoIndex built for "<<  wishedPointCountPerCell <<" points per cell: array [" << _colCount << "][" << _rowCount << "] (cellSize="<< _cellSize<<")");
	
	_cells.reserve(_colCount*_rowCount);
	for (int i = 0; i < _colCount*_rowCount; ++i)
	{
		_cells.push_back( std::set< Node*>() );
	}
}

/////////////////////////////////////////////////////////////////////

void NodeGeoIndex::dump() const
{
	std::stringstream log;
	for (int i = 0; i < _colCount*_rowCount; ++i)
	{
		log << _cells[i].size() << ";";
	}
	MDW_LOG_DEBUG("Cells stats :" << log.str());
	MDW_LOG_DEBUG("Cell Count=" << _cells.size());
}

/////////////////////////////////////////////////////////////////////

int NodeGeoIndex::cellIndex(const Node* node)
{
	PointI center = node->center_i();
	return cellIndex(center);
}

/////////////////////////////////////////////////////////////////////

int NodeGeoIndex::cellIndex(const PointI& center)
{		
	return cellIndex(rowIndex(center), colIndex(center) );
}

/////////////////////////////////////////////////////////////////////

int NodeGeoIndex::cellIndex(int rowIdx, int colIdx)
{		
	return (rowIdx*_colCount)+colIdx;
}

/////////////////////////////////////////////////////////////////////

int NodeGeoIndex::rowIndex(const PointI& center)
{
	return (int) (center[1] / _cellSize);;
}

/////////////////////////////////////////////////////////////////////

int NodeGeoIndex::colIndex(const PointI& center)
{
	return (int) (center[0] / _cellSize);		
}

/////////////////////////////////////////////////////////////////////

void NodeGeoIndex::addToIndex( Node* node)
{
	//MDW_LOG_DEBUG("Adding node " << node << " on cell " << cellIndex(node));
	cellAt(cellIndex(node)).insert(node);
}

/////////////////////////////////////////////////////////////////////

void NodeGeoIndex::removeFromIndex( Node* node)
{
	//MDW_LOG_DEBUG("Removing node " << node << " on cell " << cellIndex(node));
	cellAt(cellIndex(node)).erase(node);
}

/////////////////////////////////////////////////////////////////////

std::set<Node*>& NodeGeoIndex::cellAt(int rowIdx, int colIdx)
{	
	int cellIdx = cellIndex(rowIdx, colIdx);
	return cellAt(cellIdx);
}

/////////////////////////////////////////////////////////////////////

std::set<Node*>& NodeGeoIndex::cellAt(int cellIdx)
{	
	//MDW_LOG_DEBUG("Getting nodes on cell " << cellIdx);
	return _cells[cellIdx];
}

/////////////////////////////////////////////////////////////////////
/*
std::set<Node*>* NodeGeoIndex::safeCellAt(int colCellIdx, int rowCellIdx)
{
	if (colCellIdx < 0)
		return NULL;
	if (rowCellIdx < 0)
		return NULL;
	if (colCellIdx >= _colCount)
		return NULL;	
	if (rowCell >= _rowCount)
		return NULL;
		
	return cellAt(colCellIdx, rowCellIdx);				
}
*/
/////////////////////////////////////////////////////////////////////

std::set<std::set<Node*>* > NodeGeoIndex::nodesAtSegmentRadiusRange(const PointI& node2, const PointI& node1, int cellRadius)
{
	int colIdx1 = colIndex(node1);
	int colIdx2 = colIndex(node2);
	int rowIdx1 = rowIndex(node1);
	int rowIdx2 = rowIndex(node2);
	
	int colIdxDiff = colIdx2 - colIdx1;
	int rowIdxDiff = rowIdx2 - rowIdx1;
	int maxDiff = std::max(abs(colIdxDiff), abs(rowIdxDiff));
		
	// Avoid division by 0 ;)	
	if (maxDiff == 0)	
		return nodesAtCellRadiusRange(node1, cellRadius);
		
	std::set<std::set<Node*>* > eligiblesSet;
	
	for(int step = 0;
		step <= maxDiff;
		++step)
	{
		int colIdx = colIdx1 + ((step*colIdxDiff)/maxDiff);
		int rowIdx = rowIdx1 + ((step*rowIdxDiff)/maxDiff);
		
		// Get nodes near this position
		PointI position(colIdx, rowIdx);
		std::set<std::set<Node*>* > nodes = nodesAtCellRadiusRange(position, cellRadius);
		std::copy(nodes.begin(), nodes.end(), std::inserter(eligiblesSet, eligiblesSet.end()) );
	}
		
	return eligiblesSet;
}

std::set<std::set<Node*>* > NodeGeoIndex::nodesAtCellRadiusRange(const PointI& center, int cellRadius)
{	
	int colIdx = colIndex(center);
	int rowIdx = rowIndex(center);
	
	//MDW_LOG_DEBUG("Looking for cells around" << centerCellIndex <<  "  (" << rowIndex(center) << "," << colIndex(center) << ")");

	std::set<std::set<Node*>* > eligiblesSet;
	
	for (int cradius = cellRadius;
		 cradius <= cellRadius;
		 ++cradius)
	{
		for(int rowShift = -cradius;
			rowShift <= cradius;
			++rowShift)
		{
			if (rowIdx + rowShift < 0)
				continue;
			if (rowIdx + rowShift >= _rowCount)
				continue;
			
			int remaining = cradius - abs(rowShift);
			for(int colShift = - remaining;
				colShift <= remaining;
				++colShift)
			{		
				if (colIdx + colShift < 0)
					continue;
				if (colIdx + colShift >= _colCount)
					continue;
				
				//MDW_LOG_DEBUG("retrieving nodes from pos (" << rowIdx << "," << colIdx << ")  (" << rowShift << "," << colShift << ")");
				
				std::set<Node*>& nodes = cellAt(rowIdx+rowShift, colIdx + colShift);
				
				//MDW_LOG_DEBUG("Checking for eligibles cells at index " << shiftedCellIndex );
					
				if (nodes.empty())
					continue;

				//MDW_LOG_DEBUG("eligibles cells at index " << shiftedCellIndex << "  (" << rowShift << "," << colShift << ")");
					
				eligiblesSet.insert( & nodes );
			}
		}
	}
	
	return eligiblesSet;
}

//////////////////////////////////////////////////////////////////

void NodeGeoIndex::nearNodes(Node* node, int radius, const std::set<Node*>& excluded, std::set<Node*>& oSet)
{
	
	//MDW_LOG_DEBUG("Near nodes search ");
	
	int cellRadius = 1 + (int)(radius / _cellSize);
	PointI center = node->center_i();	
	std::set<std::set<Node*>* > eligiblesSet = nodesAtCellRadiusRange(center, cellRadius);
	
	
	//MDW_LOG_DEBUG("Near nodes of " << node << " : eligibles cells count is " << eligiblesSet.size());
	
	
	if (eligiblesSet.empty())
		return;
	
	//MDW_LOG_DEBUG("Near nodes of " << node << " : eligibles cells count is " << eligiblesSet.size());
	
	std::set<std::set<Node*>* >::iterator it;
	for(it  = eligiblesSet.begin();
		it != eligiblesSet.end();
		++it)
	{
		std::set<Node*>::const_iterator nodeIt;
		for(nodeIt  = (*it)->begin();
			nodeIt != (*it)->end();
			++nodeIt) 
		{
			Node* node2 = *nodeIt;
		
			if (node2 == node)
				continue;
		
			if (excluded.find(node2) != excluded.end())
				continue;
				
			if (node->distance(node2) > radius)
				continue;
		
			oSet.insert(node2);
		}		
		
	}		

}		

//////////////////////////////////////////////////////////////////

void NodeGeoIndex::nearNodes(Node* node1, Node* node2, int radius, std::set<Node*>& oSet)
{
	
	//MDW_LOG_DEBUG("Near nodes search ");
	
	int cellRadius = 1 + (int)(radius / _cellSize);
	PointI coord1 = node1->center_i();
	PointI coord2 = node2->center_i();
		
	std::set<std::set<Node*>* > eligiblesSet = nodesAtSegmentRadiusRange(coord1, coord2, cellRadius);
	
	//MDW_LOG_DEBUG("Near nodes of " << node << " : eligibles cells count is " << eligiblesSet.size());
		
	if (eligiblesSet.empty())
		return;
	
	//MDW_LOG_DEBUG("Near nodes of segment : eligibles cells count is " << eligiblesSet.size());
	
	std::set<std::set<Node*>* >::iterator it;
	for(it  = eligiblesSet.begin();
		it != eligiblesSet.end();
		++it)
	{
		std::set<Node*>::const_iterator nodeIt;
		for(nodeIt  = (*it)->begin();
			nodeIt != (*it)->end();
			++nodeIt) 
		{
			oSet.insert(*nodeIt);
		}		
		
	}		

}		

///////////////////////////////////////////////////////////////////

Node* NodeGeoIndex::nearestPointOnSameCell(const PointI& coord)
{
	std::set<Node*>& nodes = cellAt( cellIndex(coord) );

	if (nodes.empty())
		return NULL;
	
	Node* best = NULL;

	std::set<Node*>::const_iterator nodeIt;
	for(nodeIt  = nodes.begin();
		nodeIt != nodes.end();
		++nodeIt) 
	{			
		Node* node2 = *nodeIt;
	
		if (best == NULL)
		{
			best = node2;
			continue;
		}
					
		if (Tools::distance(coord, node2->center_i()) > Tools::distance(coord, best->center_i()))
			continue;
			
		best = node2;
	}			

	return best;
}
