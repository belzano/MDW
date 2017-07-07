#include "CmdIdentifyShapes.hpp"

#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"

#include "toolbox/Logger.hpp"

#include <iostream>
#include <set>

#include "Geometry.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Node.hpp"

#include "ShapeHandler.hpp"
#include "ShapeHandlerRegistry.hpp"


using namespace std;

////////////////////////////////////////////////////////////////////

bool CmdIdentifyShapes::search( const ConnectedSet& iSet,
								const ShapeHandlerSet& handlers,
								std::list< std::shared_ptr<Shape> >& ioFoundShapes) 
{	
	std::multimap<float, std::shared_ptr< Shape> > marks;	
	
	ConnectedSetStats stats;
	stats.compute(iSet);

	//_context.log(iSet, stats);


	// Loop on registered shapes detector, and get potential shapes with mark 
	ShapeHandlerSet::const_iterator it;
	for(it  = handlers.begin();
		it != handlers.end();
		++it )
	{
		//MDW_LOG_CONTEXT((*it)->getName());
		(*it)->findAndMark(iSet, stats, marks, _parameters);
	}
	
	if (marks.empty())
	{
		//MDW_LOG_CONTEXT("NoShapeIdentified");
		//_context.log(iSet, stats);
		return false;
	}

	// Debug: Log all marks for that shape
	std::multimap<float, std::shared_ptr<Shape> >::const_iterator markIt;
	for(markIt  = marks.begin();
		markIt != marks.end();
		++markIt)
	{
		MDW_LOG_DEBUG( "MARKS Potential shape: " << markIt->second->getName()	<< " (mark=" << markIt->first << ")" );			
	}
	MDW_LOG_INFO("-> Shape selected: " << marks.rbegin()->second->getName() << " (mark=" << marks.rbegin()->first << ")" );
										
	ioFoundShapes.push_back( marks.rbegin()->second );
	_context.log(iSet, stats);
		
	return true;
}
