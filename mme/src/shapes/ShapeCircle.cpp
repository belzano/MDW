#include "ShapeCircle.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"

#include "Node.hpp"

#include "toolbox/Logger.hpp"

//////////////////////////////////////////////////////////////////////

ShapeCircle::ShapeCircle(const ConnectedSet& set, const PointI& center, int radius) : 
	Shape(set),
	_center(center),
	_radius(radius) 
{}
	
//////////////////////////////////////////////////////////////////////
	
void ShapeCircle::serializeAsSvg(std::ostream& ioOut, 
								 const Parameters& ) const
{ 
	ioOut 	<< "<circle cx=\"" << _center[0] 
			<< "\" cy=\"" << _center[1]
			<< "\" r=\"" << _radius
			<< "\" stroke=\"blue\" stroke-width=\"5\" fill=\"none\" />";
}

//////////////////////////////////////////////////////////////////

double ShapeCircle::distance(const Node* iNode) const
{
	return abs(_radius - Tools::distance(iNode->center_i(), _center));
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	
void ShapeCircleHandler::findAndMark( const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
									std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
									const Parameters& iParams) const

{
	// TODO add precision
	if (!iStats.isConnex())
		return;
	
	PointI center;
	center[0] = (iStats.getEnclosingRectMin()[0] + iStats.getEnclosingRectMax()[0])/2;
	center[1] = (iStats.getEnclosingRectMin()[1] + iStats.getEnclosingRectMax()[1])/2;
	
	
	//float avgLenghtFromGrav = iStats.getAverageDistanceFromGravityCenter();
	//float minLenghtFromGrav = iStats._sortedDistanceFromGravCenter.begin()->first;
	//float maxLenghtFromGrav = iStats._sortedDistanceFromGravCenter.rbegin()->first;
	
	float avgLenghtFromCenter = 0;
	float minLenghtFromCenter = 10000000000;
	float maxLenghtFromCenter = 0;
	
	// Loop on Set to compute the lenght
	ConnectedSet::const_iterator setIt;
	for(setIt  = iGraph.begin();
		setIt != iGraph.end();
		++setIt)
	{
		float distance = Tools::distance(center, setIt->first->center_i());
		minLenghtFromCenter = std::min(minLenghtFromCenter, distance);
		maxLenghtFromCenter = std::max(maxLenghtFromCenter, distance);
		avgLenghtFromCenter += distance;
			
	}
	avgLenghtFromCenter /= iGraph.size();
	
	
	MDW_LOG_DEBUG("Circle params: = "<< avgLenghtFromCenter << " - " << minLenghtFromCenter << " - " << maxLenghtFromCenter );
	
	float accuracy = 0;
	for (accuracy = 0; 
		accuracy < 1;
		accuracy+=0.1)
	{	
		float lowerBound = 0.75 + 0.20 * accuracy;
		float upperBound = 1.25 - 0.20 * accuracy;
		if (minLenghtFromCenter < lowerBound* avgLenghtFromCenter ||
			maxLenghtFromCenter > upperBound* avgLenghtFromCenter)	
			break;
	}
	
	float theMarkNotAPolygon = std::min(((float)iGraph.size()) / 8, (float)1);	
	
	MDW_LOG_DEBUG("Circle accuracy = "<< accuracy << ", not a polygon = " << theMarkNotAPolygon);	 	
	float mark = accuracy * theMarkNotAPolygon;
	if (mark == 0)
		return;
	
	ioFoundShapesMarked.insert(std::make_pair(mark, build(iGraph, iStats, iParams)));
}
	
//////////////////////////////////////////////////////////////////

std::shared_ptr<Shape> ShapeCircleHandler::build(const ConnectedSet& set, const ConnectedSetStats& iStats, 
												const Parameters& ) const
{
	PointI center;
	center[0] = (iStats.getEnclosingRectMin()[0] + iStats.getEnclosingRectMax()[0])/2;
	center[1] = (iStats.getEnclosingRectMin()[1] + iStats.getEnclosingRectMax()[1])/2;
	int radius = iStats.getAverageDistanceFromGravityCenter();
	return std::shared_ptr<Shape>(new ShapeCircle(set, center, radius));	
}
