#include "ShapeLine.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"
#include "Parameters.hpp"

#include <ostream>
#include <list>
#include <set>
#include <map>


//////////////////////////////////////////////////////////////////////

ShapeLine::ShapeLine(const ConnectedSet& set, Node* node1, Node* node2) : 
			Shape(set),
		   _segment(node1, node2) 
{}

//////////////////////////////////////////////////////////////////////

void ShapeLine::serializeAsSvg(std::ostream& ioOut, 
								const Parameters& ) const
{
	PointI p1 = _segment._zone1->center_i();	
	PointI p2 = _segment._zone2->center_i();	
	
	ioOut 	<< "<line "
			<< " stroke=\"blue\" stroke-width=\"5\" "
			<< "x1=\"" << p1[0] << "\" "
			<< "y1=\"" << p1[1] << "\" "
			<< "x2=\"" << p2[0] << "\" "
			<< "y2=\"" << p2[1] << "\" ";                  
	ioOut 	<< "/>";
}

//////////////////////////////////////////////////////////////////////

double ShapeLine::distance(const Node* iPoint) const
{
	return _segment.distanceToSegment(iPoint);
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////


void ShapeLineHandler::findAndMark( const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& parameters) const 
{
	if (iStats.isClosed())
		return;
	
	// Take the point the furthest from the grav center
	Node* firstNode = iStats.getSortedDistanceFromGravCenter().rbegin()->second;

	Node* secondNode = firstNode;
	// Loop on node to get the furthest
	ConnectedSet::const_iterator aNodeIt;
	for(aNodeIt  = iGraph.begin();
		aNodeIt != iGraph.end();
		++aNodeIt)
	{
		if (firstNode->distance(secondNode) < firstNode->distance(aNodeIt->first))
			secondNode = aNodeIt->first;
	}
	
	// Create a candidate line
	std::shared_ptr<Shape>  theLine(new ShapeLine(iGraph, firstNode, secondNode) );	
	
	float lineLenght = firstNode->distance(secondNode);
	float totalErr = 0;
	
	// MaxErr is 10% line lenght or 1% reference resolution
	float maxErr = std::min( 0.1*lineLenght, 0.01*parameters._refRes);
	// Compute the average distance fromn others points to the line to get a mark
	Segment aSeg(firstNode, secondNode);
	for(aNodeIt  = iGraph.begin();
		aNodeIt != iGraph.end();
		++aNodeIt)
	{
		double dist = theLine->distance(aNodeIt->first);
		if (dist > maxErr)
			return;	
		totalErr += dist;
	}

	float mark = 1 - (totalErr / ((iGraph.size() * lineLenght))); 	
		
	ioFoundShapesMarked.insert(std::make_pair(mark, theLine));
}
	
