#include "ShapeRectangle.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"

#include "Parameters.hpp"

#include <ostream>
#include <list>
#include <set>
#include <map>


//////////////////////////////////////////////////////////////////////

ShapeRectangle::ShapeRectangle(const ConnectedSet& iSet, const PointI& corner, int width, int height) : 
		Shape(iSet),
		_corner(corner), 
		_width(width), 
		_height(height) 
{}

//////////////////////////////////////////////////////////////////////

void ShapeRectangle::serializeAsSvg(std::ostream& ioOut, 
								const Parameters& ) const
{
	
	ioOut 	<< "<rect x=\"" << _corner[0] 
			<< "\" y=\"" << _corner[1]
			<< "\" width=\"" << _width
			<< "\" height=\"" << _height
			<< "\" stroke=\"blue\" stroke-width=\"5\" fill=\"none\"/>";
}

//////////////////////////////////////////////////////////////////////

double ShapeRectangle::distance(const Node* iNode) const
{
	PointI point = iNode->center_i();
	
	int x2 = _corner[0] + _width;
    int y2 = _corner[1] + _height;
    
    int xDiff = 0;
    int yDiff = 0;
    
    // inside the rectangle
    if ((point[0] > _corner[0]) && (point[0] <x2) && (point[1] > _corner[1]) && (point[1] <y2) )
    {
		xDiff = std::min(point[0] - _corner[0], x2 - point[0]);
		yDiff = std::min(point[1] - _corner[1], y2 - point[1]);
		return std::min(xDiff, yDiff);
	}
    
    if (point[0] < _corner[0]) 
		xDiff = _corner[0] - point[0];
    if (point[0] > x2) 
		xDiff = point[0] - x2;
        
    if (point[1] < _corner[1]) 
		yDiff = _corner[1] - point[1];
    if (point[1] > y2) 
		yDiff = point[1] - y2;
    
    int distance2 = xDiff * xDiff + yDiff * yDiff;

    return sqrtf(distance2);
}
		
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void ShapeRectangleHandler::findAndMark( const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const
{
	// TODO not really a pertinent check
	if (! iStats.isClosed())
		return;

	// TODO add precision
	if (!iStats.isConnex())
		return;

	// TODO Check no backtracking when walking around gravity center
	// eg, angle only increase or decrease
	if (iStats.isPerimeterBacktracking())
		return;
	
	//   1----------2
	//   |          |
	//   0----------3
	PointF points[4];
	points[0] = iStats.getEnclosingRectMin();
	points[2] = iStats.getEnclosingRectMax();
	points[1] = iStats.getEnclosingRectMin();
	points[1][1] = iStats.getEnclosingRectMax()[1];
	points[3] = iStats.getEnclosingRectMax();
	points[3][1] = iStats.getEnclosingRectMin()[1];
	
	// Lookup for nodes near the edge
	Node* edges[4];
	edges[0] = iGraph.begin()->first;
	edges[1] = iGraph.begin()->first;
	edges[2] = iGraph.begin()->first;
	edges[3] = iGraph.begin()->first;
	
	ConnectedSet::const_iterator nodeIt;
	for(nodeIt  = iGraph.begin();
		nodeIt != iGraph.end();
		++nodeIt)
	{
		for(int i=0; i<4;++i)
		{
			float curDist  = Tools::distance(edges[i]->center_f(), points[i]);
			float testDist = Tools::distance(nodeIt->first->center_f(), points[i]);
			if (testDist < curDist)
				edges[i] = nodeIt->first;
		}
	}
	
	//   1----------2
	//   |          |
	//   0----------3
	float x1 = (edges[0]->center_f()[0]+edges[1]->center_f()[0])/2;
	float x2 = (edges[2]->center_f()[0]+edges[3]->center_f()[0])/2;
	float y1 = (edges[0]->center_f()[1]+edges[3]->center_f()[1])/2;
	float y2 = (edges[1]->center_f()[1]+edges[2]->center_f()[1])/2;
	float width  = x2 - x1;
	float height = y2 - y1;
	
	// 	adjust the rectangle
	PointF correctedEdge(x1, y1);
	
	// mark the shape, computing avg error for points 
	std::shared_ptr<ShapeRectangle> theShape(new ShapeRectangle(iGraph, correctedEdge, width, height));
	
	double mark = computeMark(theShape, iGraph, iParams);
	if (mark <= 0)
		return;
		
	ioFoundShapesMarked.insert(std::make_pair(mark, theShape));
}

////////////////////////////////////////////////////////////////////////

double ShapeRectangleHandler::computeMark(std::shared_ptr<ShapeRectangle> iShape, 
										  const ConnectedSet& iGraph, 
										  const Parameters& ) const
{
	// Check shape ratio
/*
	if (iShape->_width < 10 * iShape->_height)
		return 0;
	
	if (iShape->_height < 10 * iShape->_width)
		return 0;
		
	double minSize = 5 + 0.005 * iParams._refRes;
	if (iShape->_width < minSize)
		return 0;
	if (iShape->_height < minSize)
		return 0;
			*/	
	double deviation = 0;
	// 1% of image size + 10% of the shape size
	double allowedDeviation = 20*iGraph.size(); // 0.01 * iParams._refRes + 0.1 * sqrtf(iShape->_width * iShape->_height);
	double goodDeviation = 20;

	ConnectedSet::const_iterator nodeIt;
	for(nodeIt  = iGraph.begin();
		nodeIt != iGraph.end();
		++nodeIt)
	{
		double distance =  iShape->distance(nodeIt->first);
		// If one of the point is too far, reject the shape
		if (distance > allowedDeviation)
			return 0;
			
		if (distance > goodDeviation)	
			deviation += (distance-goodDeviation)/ ((float)iGraph.size());
	}	
	double mark = std::max<double>(0.0, 1.0 - 0.05*deviation);
	return mark;		
}

