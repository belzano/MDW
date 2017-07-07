#include "ShapeEllipse.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"

//////////////////////////////////////////////////////////////////////

ShapeEllipse::ShapeEllipse(const ConnectedSet& set, PointF center, int radius_x, int radius_y) : 
	Shape(set),
	_center(center),
	_radius_x(radius_x),
	_radius_y(radius_y)
{}
	
//////////////////////////////////////////////////////////////////////
	
void ShapeEllipse::serializeAsSvg(std::ostream& ioOut, 
								 const Parameters& ) const
{ 
	ioOut 	<< "<ellipse cx=\"" << _center[0] 
			<< "\" cy=\"" << _center[1] 
			<< "\" rx=\"" << _radius_x
			<< "\" ry=\"" << _radius_y
			<< "\" stroke=\"blue\" stroke-width=\"5\" fill=\"none\" />";
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void ShapeEllipseHandler::findAndMark( const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& ) const 
{	
	if (! iStats.isClosed())
		return;
		
	if (! iStats.isConnex())
		return;
		
	// a is the great axis	
	float a = (iStats.getEnclosingRectMax()[0] - iStats.getEnclosingRectMin()[0]) / 2;
	float b = (iStats.getEnclosingRectMax()[1] - iStats.getEnclosingRectMin()[1]) / 2;
	
	// TODO: only horizontal ellipses are handled right now
	if (a < b)
		return;
		//std::swap(a, b);		
		
	float c = sqrtf(b*b - a*a);
			
	PointF center;
	center[0] = (iStats.getEnclosingRectMin()[0] + iStats.getEnclosingRectMax()[0])/2;
	center[1] = (iStats.getEnclosingRectMin()[1] + iStats.getEnclosingRectMax()[1])/2;
	
	PointF focal1 = center;
	focal1[0] -= c;
	Node focalNode1(focal1);
	
	PointF focal2 = center;
	focal2[0] += c;
	Node focalNode2(focal2);
	
	// ensure all points respects d(M, F) + d(M, F') = a + b
	float accuracy = 0.2; //20%
	ConnectedSet::const_iterator anIt;
	for(anIt  = iGraph.begin();
		anIt != iGraph.end();
		++anIt)	
	{
		const Node* node = anIt->first;
		float focalDistSum = node->distance( & focalNode1 ) + node->distance( & focalNode2);
		if (focalDistSum > (1.0 + accuracy) * 2 * a)
			return;
		if (focalDistSum < (1.0 - accuracy) * 2 * a)
			return;
	}
	
	// It may be a circle, or even a rectangle/hexagon: so reduce
	float theMarkNotACircle = 1 - b/a;	
	float theMarkNotAPolygon = std::min(((float)iGraph.size()) / 10, (float)1);	
		 
	float mark = theMarkNotACircle * theMarkNotAPolygon;
	
	// Build the shape
	std::shared_ptr<Shape> theEllipse((new ShapeEllipse(iGraph, center, a, b)));
	ioFoundShapesMarked.insert(std::make_pair(mark, theEllipse));
}
	
