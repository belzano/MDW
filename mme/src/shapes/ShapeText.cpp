#include "ShapeText.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"
#include "Parameters.hpp"

#include "toolbox/Logger.hpp"

#include <ostream>
#include <list>
#include <set>
#include <map>


//////////////////////////////////////////////////////////////////////

ShapeText::ShapeText(const ConnectedSet& set, const PointI& corner, int width, int height) : 
		Shape(set),
		_corner(corner), 
		_width(width), 
		_height(height) 
{}

//////////////////////////////////////////////////////////////////////

void ShapeText::serializeAsSvg(std::ostream& ioOut, 
								const Parameters& ) const
{
	ioOut 	<< "<rect x=\"" << _corner[0] 
			<< "\" y=\"" << _corner[1]
			<< "\" width=\"" << _width
			<< "\" height=\"" << _height
			<< "\" stroke=\"red\" stroke-width=\"5\" fill=\"red\"/>";
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void ShapeTextHandler::findAndMark( const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const

{
	// Check lots of nodes with connexion > 2
	// Usually shorts segments and heavy nodes
	std::map<int, int> profile = iStats.getProfile();
	float singularityRatio = ((float)iGraph.size() - profile[2]) / iGraph.size();
		
	// Too much cnx 2: return
	if (singularityRatio < 0.1)
		return;
		
	// At least 1-seg and 3-segs
	//if (profile.size() <= 2)
	//	return;

/*	
	// And several nodes in this case
	int multiNodeCount = 0;
	std::map<int, int>::const_iterator profileIt;
	for(profileIt  = profile.begin();
		profileIt != profile.end();
		++profileIt)
	{
		multiNodeCount += profileIt->second;
	}
	if (multiNodeCount < 5) // TODO maybe rather a ratio from the overall size?
		return;
*/	
	// Check all lenght are smalls (<2% refSize)
	float refsize = 0.02* iParams._refRes;
	ConnectedSet::const_iterator setIt;
	for(setIt  = iGraph.begin();
		setIt != iGraph.end();
		++setIt)
	{
		std::set<Node*>::const_iterator nodeIt;
		for(nodeIt  = setIt->second.begin();
			nodeIt != setIt->second.end();
			++nodeIt)
		{
			// prevent doing the comparison twice
			if (*nodeIt < setIt->first)
				continue;
			
			float distance = Tools::distance((*nodeIt)->center(), setIt->first->center());
			if (distance > refsize)
			{
				MDW_LOG_DEBUG("line too long to accept as TEXT : " << distance << " (max is " << refsize << ")")
				return;
			}
		}

	}
	
	
	PointF p1, p2;
	p1 = iStats.getEnclosingRectMin();
	p2 = iStats.getEnclosingRectMax();
	
	ioFoundShapesMarked.insert( { singularityRatio, std::shared_ptr<Shape>(new ShapeText(iGraph, p1, p2[0]-p1[0], p2[1]-p1[1])) } );
}
