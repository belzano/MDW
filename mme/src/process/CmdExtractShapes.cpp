#include "CmdExtractShapes.hpp"

#include "CmdIdentifyShapes.hpp"

#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

#include "QueryContext.hpp"

#include <iostream>
#include <set>

#include "Geometry.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

void CmdExtractShapes::execute (QueryContext& iQuery, 
								ConnectedSet& iGraph, 
								list<std::shared_ptr<Shape> >& oShapes)
{
	CmdExtractShapes aCmd(iQuery, iQuery.getParameters());
	aCmd.process(iGraph, oShapes);
}

////////////////////////////////////////////////////////////////////

int CmdExtractShapes::process (ConnectedSet& theInitialSet,
								list<std::shared_ptr<Shape> >& ioShapes)
{
	
	//////////////////////////////////////////////////////////
	// Split disconnected sets
	//////////////////////////////////////////
	
	std::list< ConnectedSet > theSourceSetsList;	
	{
		MDW_LOG_CONTEXT("Split");
		GetSubSets(SubSetType::Disjoint, theInitialSet, theSourceSetsList);
	}

	//////////////////////////////////////////////////////////
	// Try to fond closed sets and analyse them
	// remainings nodes are returned
	//////////////////////////////////////////////////////////
	std::list< ConnectedSet > theUnidentifiedSets;
	{
		MDW_LOG_CONTEXT("ExtractClosed");
		extractShapes(theSourceSetsList, SubSetType::Closed, *ClosedShapeHandlerRegistry::instance, theUnidentifiedSets, ioShapes, 0.05);
	
		MDW_LOG_DEBUG(	"Connected set extraction: Source set list: " << theSourceSetsList.size() <<
						"Unidentified list: " << theUnidentifiedSets.size() <<
						"Shapes list" << ioShapes.size() );
		{
			MDW_LOG_CONTEXT("Residual");
			_context.log(theUnidentifiedSets);
		}				
	}
	
	//////////////////////////////////////////////////////////
	// Analyse remains to convert in any shape known
	// remainings nodes are returned
	//////////////////////////////////////////////////////////
	std::list<ConnectedSet> theUnidentifiedSets2;
	{
		MDW_LOG_CONTEXT("ExtractAny");	
		extractShapes(theUnidentifiedSets, SubSetType::Identity, *ShapeHandlerRegistry::instance, theUnidentifiedSets2, ioShapes, 0.01);
		
		MDW_LOG_DEBUG(	"All set extraction: Source set list: " << theUnidentifiedSets.size() <<
						"Unidentified list: " << theUnidentifiedSets2.size() <<
						"Shapes list" << ioShapes.size() );
		{
			MDW_LOG_CONTEXT("Residual");
			_context.log(theUnidentifiedSets2);
		}
	}
	
	//////////////////////////////////////////////////////////
	// Convert remains to a list of line. 
	// Try to rebuild shapes from those lines
	// remainings nodes are returned
	//////////////////////////////////////////////////////////
	std::list<ConnectedSet> theUnidentifiedSets3;
	{
		MDW_LOG_CONTEXT("ExtractLines");	
		extractShapes(theUnidentifiedSets2, SubSetType::Lines, *ShapeHandlerRegistry::instance, theUnidentifiedSets3, ioShapes, 0);
		
		MDW_LOG_DEBUG(	"All set extraction: Source set list: " << theUnidentifiedSets2.size() <<
						"Unidentified list: " << theUnidentifiedSets3.size() <<
						"Shapes list" << ioShapes.size() );
		{
			MDW_LOG_CONTEXT("Residual");
			_context.log(theUnidentifiedSets3);
		}
	}
	
	//////////////////////////////////////////////////////////
	// - Grab the lonely small shapes
	// - Try to regroup near, it may be text...
	
	// list <refCenter, refSize>
	
	// build groups
	// list< list<Shapes>, list<ConnectedSet> >
	
	// Convert to ShapeText


	
	//List(connected set), list(shape)
	//->Try composite identification

	return 0;
}

//////////////////////////////////////////////////////////////////

/* nodeAbsorption()
 
	// Second step: Absorb from remaing sets at node level ??
	std::list<ConnectedSet> theUnidentifiedSets2;
	std::list<ConnectedSet>::iterator aSetIt;
	for(aSetIt  = theSourceSetsList.begin();
		aSetIt != theSourceSetsList.end();
		++aSetIt)
	{
		// if too small, forget it
		MDW_LOG_CONTEXT("Residual graph");
		_context.log(*aSetIt);
		
		// 
		std::list<std::shared_ptr<Shape> >::const_iterator shapeIt;
		for(shapeIt  = ioShapes.begin();
			shapeIt != ioShapes.end();
			++shapeIt)
		{
			if (removeOverlap(*aSetIt, *shapeIt)) 
				theUnidentifiedSets2.push_back(*aSetIt);
		}
	}
*/

////////////////////////////////////////////////////////////////////////

void CmdExtractShapes::extractShapes(const std::list<ConnectedSet>& theSourceSetsList, 
									SubSetType type,
									 const ShapeHandlerSet& handlers,
									  std::list<ConnectedSet>& oResidualSetsToAnalyse,
									 std::list<std::shared_ptr<Shape> >& ioShapes,
									 float sizeRatio)
{
	MDW_LOG_CONTEXT("ExtractSubsets");
	
	std::list<ConnectedSet> theResidualSets;
	
	MDW_LOG_DEBUG("distincts sets separation");
	std::list< ConnectedSet >::const_iterator theSourceSetIt;
	for(theSourceSetIt  = theSourceSetsList.begin();
		theSourceSetIt != theSourceSetsList.end();
		++theSourceSetIt)
	{
		extractShapes(*theSourceSetIt, type, handlers, oResidualSetsToAnalyse,sizeRatio, ioShapes);	
	}
}

////////////////////////////////////////////////////////////////////

void CmdExtractShapes::extractShapes(const ConnectedSet& theSourceSet, 
									SubSetType type,
									 const ShapeHandlerSet& handlers,
									 std::list<ConnectedSet>& oResidualSetsToAnalyse,
									 float sizeRatio,
									 std::list<std::shared_ptr<Shape> >& ioShapes)
{
	MDW_LOG_DEBUG("Analyzing subsets");
	std::list<ConnectedSet> theSubSets;
	GetSubSets(type, theSourceSet, theSubSets);
	
	MDW_LOG_INFO("Found " << theSubSets.size() <<  " subsets");
	
	// Filter to keep only biggest closed sets
	std::list<ConnectedSet> smallSets ; 
	filterBySize(theSubSets, sizeRatio, smallSets);
	// Artificially group the small sets (Could be detached text)
	//groupSmallSets(smallSets, oResidualSetsToAnalyse, theSubSets);

	// Shapes identification from sets
	std::list<ConnectedSet> theIdentifiedSets;
	identifyShapes(theSubSets, handlers, ioShapes, theIdentifiedSets);
	MDW_LOG_INFO("Identified " << theIdentifiedSets.size() << "/"  << theSubSets.size() << " subsets");
			
	MDW_LOG_DEBUG("Getting residual sets");
	getResidualSubsets(theSourceSet, theIdentifiedSets, oResidualSetsToAnalyse);
}
	
////////////////////////////////////////////////////////////////////

void CmdExtractShapes::groupSmallSets(const std::list<ConnectedSet>& iSets, std::list<ConnectedSet>& oNotUsed, std::list<ConnectedSet>& oCreated)
{
	std::list<ConnectedSet> sets = iSets;
	
	std::list<ConnectedSet>::const_iterator it;
	for(it  = sets.begin();
		it != sets.end();
		++it)
	{
		bool newGroup = false;
		ConnectedSet newSet = *it;
		ConnectedSetStats stats;
		stats.compute(newSet);

		std::list<ConnectedSet>::const_iterator it2;
		for(it2  = it;
			it2 != sets.end();
			++it2)
		{
			if (it2 == it)
				continue;
				
			ConnectedSetStats stats2;
			stats2.compute(*it2);
			
			if (Tools::distance(stats.getGravityCenter(), stats2.getGravityCenter()) < 0.10*_parameters._refRes)
			{
				newGroup = true;
				newSet.merge(*it2);
			}
			else
			{
				++it2;
			}
		}
		
		if (newGroup)
		{
			MDW_LOG_CONTEXT("New group created");
			_context.log(newSet);
			oCreated.push_back(newSet);
		}
		else
		{
			oNotUsed.push_back(*it);
		}

	}
}
	
////////////////////////////////////////////////////////////////////

void CmdExtractShapes::filterBySize(std::list<ConnectedSet>& ioSets, double distFromGravRatio, std::list<ConnectedSet>& oRemoved)
{
	std::list<ConnectedSet>::iterator it;
	for(it  = ioSets.begin();
		it != ioSets.end();
		)
	{
		ConnectedSetStats stats;
		stats.compute(*it);
	
		// If enclosing rec is too small, throw the ConnectedSet away
		if (stats.getSortedDistanceFromGravCenter().rbegin()->first < distFromGravRatio*_parameters._refRes)
		{
			MDW_LOG_CONTEXT("SmallSetSkipped");
			oRemoved.push_back(*it);
			it = ioSets.erase(it);
		}
		else
		{
			++it;
		}
	}
}
		
////////////////////////////////////////////////////////////////////
/*
void CmdExtractShapes::convertFromGraphToConnectedSet (const Graph& iGraph,
														ConnectedSet& ioSet)
{
	Graph::const_iterator aGraphIt;
	for (aGraphIt  = iGraph.begin();
		 aGraphIt != iGraph.end();
		 ++aGraphIt)
	{	
		Node* node = *aGraphIt;
		
		std::list<Segment*>::const_iterator aSegIt;
		for(aSegIt  = node->_segments.begin();
			aSegIt != node->_segments.end();
			++aSegIt)
		{
			Node* node2 = (*aSegIt)->otherNode(node);
			ioSet.link(node, node2);
		}
	}	
	
}
*/
////////////////////////////////////////////////////////////////////

void CmdExtractShapes::getResidualSubsets (const ConnectedSet& iOriginal,
										   const list<ConnectedSet >& ioClosedSets,
										   list<ConnectedSet >& ioOpenedSets)
{
	ConnectedSet remaining = iOriginal;
	
	std::list<ConnectedSet>::const_iterator anConSetIt;
	for(anConSetIt  = ioClosedSets.begin();
		anConSetIt != ioClosedSets.end();
		++anConSetIt)
	{
		remaining.unlink(*anConSetIt);
	}
	
	// Remove all links included in those connected sets
	ConnectedSet::iterator aSetIt;
	for(aSetIt  = remaining.begin();
		aSetIt != remaining.end();
		++aSetIt)
	{
		if (aSetIt->second.empty())
			remaining.erase(aSetIt->first);
	}
	
	//MDW_LOG_DEBUG("Remaining points");	
	//_context.log(remaining);
	
	GetSubSets(SubSetType::Disjoint, remaining, ioOpenedSets);
}

///////////////////////////////////////////////////////////////////

void CmdExtractShapes::GetSubSets(SubSetType type, const ConnectedSet& iSet, std::list<ConnectedSet>& ioSplittedSets)
{
	switch(type)
	{
		case SubSetType::Disjoint:
			_cmdSplit.splitPaint(iSet, ioSplittedSets);
			break;
		case SubSetType::Closed:
			_cmdSplit.ClosedPathLookup(iSet, ioSplittedSets);
			break;
		case SubSetType::Identity:
			ioSplittedSets.push_back(iSet);
			break;
		case SubSetType::Lines:
			_cmdSplit.splitAtAngles(iSet, ioSplittedSets);
			break;
	}
}

///////////////////////////////////////////////////////////////////

bool CmdExtractShapes::couldBeAbsorbed(	const ConnectedSet& iConnectedSet,
										const std::list<std::shared_ptr<Shape> >& ioShapes)
{
	std::list<std::shared_ptr<Shape> >::const_iterator shapeIt;
	for(shapeIt  = ioShapes.begin();
		shapeIt != ioShapes.end();
		++shapeIt)
	{
		if ((*shapeIt)->couldAbsorb(iConnectedSet))
			return true;
	}
	
	return false;
}

////////////////////////////////////////////////////////////////////////

bool CmdExtractShapes::removeOverlap(	ConnectedSet& iSet,
										const std::shared_ptr<Shape>& iShape)
{
	bool changes = false;
	std::set<std::pair<Node*, Node*> > toRemove;
	
	ConnectedSet::iterator anIt;
	for(anIt  = iSet.begin();
		anIt != iSet.end();
		++anIt)
	{
		if (iShape->distance(anIt->first) > 20)
			continue;
		
		std::set<Node*> overlapped = anIt->second;
		
		std::set<Node*>::iterator aNodeIt;
		for(aNodeIt  = anIt->second.begin();
			aNodeIt != anIt->second.end();
			++aNodeIt)
		{
			if (iShape->distance(*aNodeIt) > 20)
				continue;
				
			toRemove.insert( {anIt->first, *aNodeIt});
		}
	}
	
	if (! toRemove.empty())
	{
		std::set<std::pair<Node*, Node*> >::iterator aPairIt;
		for(aPairIt  = toRemove.begin();
			aPairIt != toRemove.end();
			++aPairIt)
		{
			iSet.unlink(aPairIt->first, aPairIt->second);
		}
			
		changes = true;
	}
	
	return changes;
}


////////////////////////////////////////////////////////////////////

void CmdExtractShapes::identifyShapes( 	const std::list<ConnectedSet >& iConnectedSets,
										const ShapeHandlerSet& handlers,
										std::list<std::shared_ptr<Shape> >& ioShapes,
										std::list<ConnectedSet >& theIdentifiedSets)
{
	MDW_LOG_CONTEXT("Identify");
	CmdIdentifyShapes theIdentificationCmd(_context, _parameters);
	
	int shapeIndex = 0;
	std::list<ConnectedSet>::const_iterator aSetIt;		
	for(aSetIt  = iConnectedSets.begin();
		aSetIt != iConnectedSets.end();
		++aSetIt)
	{
		shapeIndex++;
		
		// Check if this set may be absorbed by an already discovered shape
		if (couldBeAbsorbed(*aSetIt, ioShapes))
		{
			MDW_LOG_DEBUG("Shape #" << shapeIndex << " absorption.");
			theIdentifiedSets.push_back(*aSetIt);
			continue;
		}
		
		bool setIdentified = theIdentificationCmd.search(*aSetIt, handlers, ioShapes);
		MDW_LOG_DEBUG("Shape #" << shapeIndex << (setIdentified? " identified": "not identified"));
		if (setIdentified)
			theIdentifiedSets.push_back(*aSetIt);
	}
	
}
