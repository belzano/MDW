#include "CmdNodeGraphSplit.hpp"

#include "ConnectedSet.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

#include "QueryContext.hpp"

#include <iostream>
#include <set>

#include "Geometry.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////

bool CmdNodeGraphSplit::ClosedPathLookup( const ConnectedSet& ioGraph,
										  std::list<ConnectedSet>& ioOutPaths)
{
	std::set<Node*> alreadyVisited;
	
	// First, start from leaves, and flag all points as already visited
	ConnectedSet::const_iterator aNodeIt;
	for(aNodeIt  = ioGraph.begin();
		aNodeIt != ioGraph.end();
		++aNodeIt)
	{
		if (aNodeIt->second.size() >= 2)
			continue;
		
		Node* leafNode = aNodeIt->first;
		if (alreadyVisited.find(leafNode) != alreadyVisited.end())
			continue;
		
		alreadyVisited.insert(leafNode);	
		visitLeaves(ioGraph, leafNode, alreadyVisited);
	}
	
	{
		//MDW_LOG_CONTEXT("Visited nodes (leaves)");
		//_context.log(alreadyVisited);
	}

	// now try to find closed, starting from node 3 and more (helps to mark nodes as visited)
	for(aNodeIt  = ioGraph.begin();
		aNodeIt != ioGraph.end();
		++aNodeIt)
	{
		if (aNodeIt->second.size() <= 2)
			continue;
			
		if (alreadyVisited.find(aNodeIt->first) != alreadyVisited.end())
			continue;
		
		Node* initNode = aNodeIt->first;
		
		ConnectedSet aNodeList;
		recursiveClosedPathLookup(ioGraph, initNode, aNodeList, NULL, initNode, ioOutPaths, alreadyVisited, true, Rotation::Any);

		//MDW_LOG_CONTEXT("Visited nodes after recursion");
		//_context.log(alreadyVisited);
	}
	
	// now try to find from remaining. (Not so much should remai)
	for(aNodeIt  = ioGraph.begin();
		aNodeIt != ioGraph.end();
		++aNodeIt)
	{
		if (aNodeIt->second.size() != 2)
			continue;
			
		if (alreadyVisited.find(aNodeIt->first) != alreadyVisited.end())
			continue;
		
		Node* initNode = aNodeIt->first;
		
		ConnectedSet aNodeList;
		recursiveClosedPathLookup(ioGraph, initNode, aNodeList, NULL, initNode, ioOutPaths, alreadyVisited, true, Rotation::Any);
	}	
	 
	return ! ioOutPaths.empty();
}

/////////////////////////////////////////////////////////////////////

void CmdNodeGraphSplit::splitAtAngles(const ConnectedSet& ioGraph, 
									  std::list<ConnectedSet>& ioOutPaths)
{
	ConnectedSet theWorkingCopy = ioGraph;
	
	while (!theWorkingCopy.empty())
	{
		ConnectedSet theSet;
		ExtractSimplePath(theWorkingCopy, theSet);
		theWorkingCopy.unlink(theSet);	
		ioOutPaths.push_back(theSet);
	}
}
	
/////////////////////////////////////////////////////////////////////

void CmdNodeGraphSplit::ExtractSimplePath(const ConnectedSet& ioGraph, 
										 ConnectedSet& ioResult)
{
	// First, start from leaves
	ConnectedSet::const_iterator aNodeIt;
	for(aNodeIt  = ioGraph.begin();
		aNodeIt != ioGraph.end();
		++aNodeIt)
	{
		if (aNodeIt->second.size() >= 2)
			continue;

		visitUntilSingularity(ioGraph, aNodeIt, ioResult);
		return;
	}
	
	// Try to get start at singularities
	for(aNodeIt  = ioGraph.begin();
		aNodeIt != ioGraph.end();
		++aNodeIt)
	{
		// TODO angle check?
		if (aNodeIt->second.size() <= 2)
			continue;
		
		visitUntilSingularity(ioGraph, aNodeIt, ioResult);
		return;
	}
	
	// No more leaf
	ioResult = ioGraph;
}

/////////////////////////////////////////////////////////////////////

void CmdNodeGraphSplit::visitUntilSingularity( const ConnectedSet& iSrc, 
											   ConnectedSet::const_iterator iNodeIt,
											   ConnectedSet& ioSet)
{
	ioSet.add(iNodeIt->first);
	
	// Singularity: return
	if (iNodeIt->second.size() > 2)
		return;
	
	// Check angle if CNX-2 node
	if (iNodeIt->second.size() == 2)
	{
		Segment fromSeg(*iNodeIt->second.rbegin(), iNodeIt->first);
		Segment toSeg(iNodeIt->first, *iNodeIt->second.begin());		
		float angularVariation = toSeg.theta(iNodeIt->first) - fromSeg.theta(*iNodeIt->second.rbegin());
		if (abs(angularVariation) > 30)
			return;
	}
	
	// Explore next node
	std::set<Node*>::iterator childIt;	
	for(childIt  = iNodeIt->second.begin();
		childIt != iNodeIt->second.end();
		++childIt)
	{	
		if (ioSet.find(*childIt) != ioSet.end())
			continue;
		
		ioSet.link(iNodeIt->first, *childIt);
		visitUntilSingularity(iSrc, iSrc.find(*childIt), ioSet);
		return;
	}
}

//////////////////////////////////////////////////////////////////////

void CmdNodeGraphSplit::visitLeaves( const ConnectedSet& iSrc, Node* iLeaf,
									 std::set<Node*>& ioLeaves)
{
	ConnectedSet::const_iterator iLeafIt = iSrc.find(iLeaf);

	std::set<Node*>::iterator childIt;	
	for(childIt  = iLeafIt->second.begin();
		childIt != iLeafIt->second.end();
		++childIt)
	{	
		if (ioLeaves.find(*childIt) != ioLeaves.end())
			continue;
		
		if (iSrc.find(*childIt)->second.size() > 2)
			continue;
			
		ioLeaves.insert(*childIt);
		visitLeaves(iSrc, *childIt, ioLeaves);
	}
}

//////////////////////////////////////////////////////////////////////
/*
void CmdNodeGraphSplit::selectExplorable(const ConnectedSet& iSrc, Node* iFirst,
										 ConnectedSet& path, Node* iPrevious, Node* iCurrent,
										 std::list<ConnectedSet>& ioOutPaths,
										 std::set<Node*>& ioVisited, bool canFlagAsVisited,
										 Rotation rotationFlag, 
										 std::set<Node*> ioExplorables)
{


	
} 
*/
//////////////////////////////////////////////////////////////////////

bool CmdNodeGraphSplit::recursiveClosedPathLookup( const ConnectedSet& iSrc, Node* iFirst,
												   ConnectedSet& path, Node* iPrevious, Node* iCurrent,
											       std::list<ConnectedSet>& ioOutPaths,
											       std::set<Node*>& ioVisited, bool canFlagAsVisited,
											       Rotation rotationFlag)
{
	ConnectedSet::const_iterator iCurrentIt = iSrc.find(iCurrent);
	
	// Reevaluate for this node.
	// Flag can be propagated if one or less exit is marked as not visited
	bool canFlagAsVisitedForCurrent = false;
	if (canFlagAsVisited)
	{	
		if (iPrevious == NULL)
		{
			canFlagAsVisitedForCurrent = true;
		}
		else
		{
			int exitCount = 0;
			std::set<Node*>::iterator currentChildIt;	
			for(currentChildIt  = iCurrentIt->second.begin();
				currentChildIt != iCurrentIt->second.end();
				++currentChildIt)
			{
				// Child is the previous
				if (*currentChildIt == iPrevious)
					continue;
				
				// Child is the first node
				if (*currentChildIt == iFirst)
					continue;
				
				// Child already visited	
				if (ioVisited.find(*currentChildIt) != ioVisited.end())
					continue;
					
				++exitCount;
			}
			canFlagAsVisitedForCurrent = exitCount <= 1;
		}
	}
	
	if (canFlagAsVisitedForCurrent)
	{
		ioVisited.insert(iCurrent);
		//MDW_LOG_CONTEXT("No other choice: consider me visited");
		//_context.log(ioVisited);
	}
	
	std::set<Node*>::iterator anIt;	
	for(anIt  = iCurrentIt->second.begin();
		anIt != iCurrentIt->second.end();
		++anIt)
	{
		Node* node = *anIt;
	
		// Always go forward
		if (node == iPrevious)
			continue;
			
		// Loop completed: connected set closure
		if (node == iFirst)
		{		
			//std::cout << "Adding closing link " << *iFirst << *iCurrent << std::endl;
			path.link(iCurrent, node);
			
			//Prevent backtracking producing segments	
			ioOutPaths.push_back(path);
			
			//{				
			//   MDW_LOG_CONTEXT("FoundClosetSet");
			//    _context.log(path);
			//}
			
			path.unlink(iCurrent, node);	
			continue;
		}
	
		if (ioVisited.find(node) != ioVisited.end())
			continue;
			
		//if (iSrc.find(node)->second.size() < 2 )
		//	continue;
	
		// Ensure node is not already in graph (Prevent backtracking)
		if (path.find(node) != path.end())
			continue;
	
		//TODO parameters const int angularVariationConsideredAsDirChange = 30;
		
		// Compute angle variation when following this segment
		float angularVariation = 0;
		if (iPrevious != NULL)
		{
			Segment fromSeg(iPrevious, iCurrent);
			Segment toSeg(iCurrent, node);
			angularVariation = toSeg.theta(iCurrent) - fromSeg.theta(iPrevious);
			if (angularVariation < -180)
				angularVariation += 360;
			if (angularVariation > 180)
				angularVariation -= 360;	
		}
		/*
		// Ensure rotation flag allow to follow this direction
		if (rotationFlag == Rotation::Clockwise && angularVariation > 30)
		{
			//MDW_LOG_DEBUG("Interrupting visit (Clockwise): Angular variation:" << angularVariation );
			
			// Small deviation tolerance: allow if angle < 90 and distance from previous segment is not so huge
			if (angularVariation > 90)
				continue;
			if ( Segment(iPrevious, iCurrent).distanceToLine(node) > 10)	
				continue;
		}
			
		if (rotationFlag == Rotation::Trigo && angularVariation < -30)
		{
			//MDW_LOG_DEBUG("Interrupting visit (Clockwise): Angular variation:" << angularVariation );
			
			// Small deviation tolerance: allow if angle < 90 and distance from previous segment is not so huge
			if (angularVariation < -90)
				continue;
			if ( Segment(iPrevious, iCurrent).distanceToLine(node) > 10)	
				continue;
		}
		*/
		// Recompute the rotation flag	
		Rotation rotationFlagForCurrent = rotationFlag;
		if (rotationFlag == Rotation::Any)
		{
			if (angularVariation > 30)
				rotationFlagForCurrent = Rotation::Trigo;
			if (angularVariation < -30)
				rotationFlagForCurrent = Rotation::Clockwise;
		}
			
		//std::cout << "Adding link " << *node << *iCurrent << std::endl;		
		path.link(iCurrent, node);		
		recursiveClosedPathLookup(iSrc, iFirst, path, iCurrent, node, ioOutPaths, ioVisited, canFlagAsVisitedForCurrent, rotationFlagForCurrent);
		path.unlink(iCurrent, node);
	}
		
	return false;
}

//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void CmdNodeGraphSplit::splitPaint(const ConnectedSet& iSet, 
								  std::list< ConnectedSet >& ioConnectedSets) 
{
	std::map<Node*, int> colors;
	int lastFreeColor = 0;
	
	ConnectedSet::const_iterator aCsIt;
	for (aCsIt  = iSet.begin();
		 aCsIt != iSet.end();
		 ++aCsIt)
	{
		// skip already painted nodes
		if (colors.find(aCsIt->first) != colors.end())
			continue;
			
		colors[aCsIt->first] = lastFreeColor++;
		recursivePaintNeighbours(iSet, aCsIt->first, colors);
	}
	
	vector< ConnectedSet > connectedSet;
	connectedSet.resize(lastFreeColor);
	connectedSet.reserve(lastFreeColor);
	
	std::map<Node*, int>::iterator aMapIt;
	for (aMapIt  = colors.begin();
		 aMapIt != colors.end();
		 ++aMapIt)
	{	
		Node* node = aMapIt->first;
		
		ConnectedSet::const_iterator attachedSegments = iSet.find(node);
		std::set<Node*>::const_iterator otherNodeIt;
		for(otherNodeIt  = attachedSegments->second.begin();
			otherNodeIt != attachedSegments->second.end();
			++otherNodeIt)
		{
			Node* node2 = *otherNodeIt;
			connectedSet[aMapIt->second].link(node, node2);
		}
	}
	
	std::copy(connectedSet.begin(), connectedSet.end(), std::back_inserter(ioConnectedSets));
}

//////////////////////////////////////////////////////////////////////

void CmdNodeGraphSplit::recursivePaintNeighbours(const ConnectedSet& iSet,
												Node* iNode, 
												std::map<Node*, int>& colors) 
{		
	ConnectedSet::const_iterator theSetIt = iSet.find(iNode);
	
	std::set<Node*>::const_iterator aNodeIt;
	for (aNodeIt  = theSetIt->second.begin();
		 aNodeIt != theSetIt->second.end();
		 ++aNodeIt)
	{
		if (colors.find(*aNodeIt) != colors.end())
			continue;
		
		colors[*aNodeIt] = colors[iNode];
		recursivePaintNeighbours(iSet, *aNodeIt, colors);
	}
}

