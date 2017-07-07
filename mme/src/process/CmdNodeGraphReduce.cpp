#include "CmdNodeGraphReduce.hpp"

#include "ConnectedSet.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

#include <iostream>
#include <set>

#include "Geometry.hpp"


//#define CHRONO(x) toolbox::ScopedChrono aChrono(x);
#define CHRONO(x)

using namespace std;

////////////////////////////////////////////////////////////////////

void CmdNodeGraphReduce::execute(QueryContext& iContext,
								  ConnectedSet& ioGraph)
{
	CmdNodeGraphReduce aCmd(iContext, iContext.getParameters());
	aCmd.process(iContext, ioGraph);			
}

////////////////////////////////////////////////////////////////////

CmdNodeGraphReduce::CmdNodeGraphReduce(QueryContext& iContext, 
										const Parameters& iParams) 
										: _context(iContext),
										  _parameters(iParams)
{			
}

////////////////////////////////////////////////////////////////////

void CmdNodeGraphReduce::process(QueryContext& /*iContext*/,
								  ConnectedSet& ioGraph)
{
	// Parameters
	float nodeMergeRadius = _parameters._nodeMergeRadius;
	float lineHookRadius  = _parameters._lineHookRadius;
	float concatAngleMax  = _parameters._maxAngleErrConcat;
	float concatLineGap   = _parameters._nodeMergeRadius_LineAbsorption;
	MDW_LOG_INFO("Graph reduction: " 
					<< "nodeMergeRadius:" << nodeMergeRadius 
					<< ",lineHookRadius:" << lineHookRadius
					<< ",concatAngleMax:" << concatAngleMax
					<< ",concatLineGap:" << concatLineGap );	
	
	_geoIndex.init(_parameters._hRes, _parameters._vRes, ioGraph.size());

	// Add nodes to the index
	// - Loop on nodes
	ConnectedSet::iterator node1It;		
	for (node1It  = ioGraph.begin();
		 node1It != ioGraph.end();
		 ++node1It) 
	{
		Node* node = node1It->first;
		_geoIndex.addToIndex(node);
	}
					
	// Reduction
	// Loops 1 to 5: progressively grouping neighbours 
	// Loops 6 to 10: Add merge Hook segments
	{
		MDW_LOG_CONTEXT("GraphReduction");
		
		int stepCount = 10;
		for (int stepIdx = 1; stepIdx <= stepCount; ++stepIdx)
		{
			MDW_LOG_CONTEXT("Loop_" << toolbox::ToString(stepIdx) );
			
			float progressiveNodeMergeRadius = stepIdx * nodeMergeRadius / stepCount;
			geometry_mergeNeighbourNodes(ioGraph, progressiveNodeMergeRadius);	
			
			if (stepIdx < 5)
			{		
#ifdef MME_DEBUG 	
				_context.log(ioGraph);		
#endif 	
				continue;
			}
				
			// TODO Check if really useful since the erode was rewritteen
			float progressiveLineHookRadius = stepIdx * lineHookRadius / stepCount;
			geometry_hookNeighbourSegmentToNode(ioGraph, progressiveLineHookRadius);
		
			graph_concatConsecutiveSegments(ioGraph, 1, 1);	
			
			if (stepIdx == 9)
				extrapolateLeaves(ioGraph, _parameters._leafSegmentsConnectionMaxGap);
				
#ifdef MME_DEBUG 	
			_context.log(ioGraph);		
#endif 
		}	
	}
	
	
	
	{
		MDW_LOG_CONTEXT("realign");
	
		realign(ioGraph);
	
#ifdef MME_DEBUG 	
			_context.log(ioGraph);		
#endif 
	}
	
	
	/*
	// Reapply Reduction loop
	{
		MDW_LOG_CONTEXT("GraphReduction2");
		
		int stepCount = 5;
		for (int stepIdx = 1; stepIdx <= stepCount; ++stepIdx)
		{
			MDW_LOG_CONTEXT("Loop_" << toolbox::ToString(stepIdx) );
		
			float progressiveConcatLineGap  = stepIdx * concatLineGap / stepCount;
			float progressiveConcatMaxAngle = stepIdx * concatAngleMax / stepCount;	
			graph_concatConsecutiveSegments(ioGraph, progressiveConcatMaxAngle, progressiveConcatLineGap);	
		
			geometry_mergeNeighbourNodes(ioGraph, nodeMergeRadius);					
		
			geometry_hookNeighbourSegmentToNode(ioGraph, lineHookRadius);
				
						
#ifdef MME_DEBUG 	
			_context.log(ioGraph);		
#endif 
		}	
	}
	
	extrapolateLeaves(ioGraph, 10);
	*/
	_context.log(ioGraph);	
}

////////////////////////////////////////////////////////////////////

void CmdNodeGraphReduce::graph_buildGraph(const vector<LineI>& lines,
										   ConnectedSet& oSet)
{
	CHRONO("graph_buildGraph");
	
	//uint zoneRadius = 1;
	
    for (uint i = 0; i < lines.size(); ++i)  
    {  		
		PointF point1(lines[i][0], lines[i][1]);
		PointF point2(lines[i][2], lines[i][3]);
		Node* node1 = NULL;
		Node* node2 = NULL;

		// Check if falling into a zone. 
		Node* nearest = _geoIndex.nearestPointOnSameCell(point1);
		if (nearest != NULL &&  Tools::distance(point1, nearest->center()) < 1)
		{
			node1 = nearest;
		}
		
		nearest = _geoIndex.nearestPointOnSameCell(point2);
		if (nearest != NULL &&  Tools::distance(point2, nearest->center()) < 1)
		{
			node2 = nearest;
		}
		
		// If not, create a  zone
		if (node1 == NULL)
		{
			node1 = new Node(point1);
			oSet.add(node1);
			_geoIndex.addToIndex(node1);
		}
		
		if (node2 == NULL)
		{
			node2 = new Node(point2);
			oSet.add(node2);
			_geoIndex.addToIndex(node2);
		}
				
		oSet.link(node1, node2);
	}
	
	MDW_LOG_DEBUG("Graph built: " << oSet.size() << " nodes");
}

////////////////////////////////////////////////////////////////////

void CmdNodeGraphReduce::geometry_mergeNeighbourNodes(ConnectedSet& ioGraph, 
														  int zoneRadius)
{
	CHRONO("geometry_mergeNeighbourNodes");	
	
	//  n-------n-n------n
	//  becomes           
	//  n-------n-n------n

	//  n-------n n
	//             *  
	//              *  
	//               n
	// becomes (intersection point)
	//  n--------n
	//            * 
	//             * 
	//              n
		
	// 1- create set of points to merge
	std::list<std::set<Node*> > toMergeSets;
	std::set<Node*> 			toMergeNodes;
			
	// - Loop on nodes
	ConnectedSet::iterator node1It;		
	for (node1It  = ioGraph.begin();
		 node1It != ioGraph.end();
		 ++node1It) 
	{
		Node* node = node1It->first;
		
		// skip already selected nodes
		if (toMergeNodes.find(node) != toMergeNodes.end())
			continue;
		
		std::set<Node*> nearNodes;
		_geoIndex.nearNodes(node, zoneRadius, toMergeNodes, nearNodes);
		
		// neighbours found ?
		if (nearNodes.empty())
			continue;
			
		nearNodes.insert(node);
		std::copy(nearNodes.begin(), nearNodes.end(), std::inserter(toMergeNodes, toMergeNodes.end()));
		toMergeSets.push_back(nearNodes);	
	}
		
	
	// Loop on mergeSetd to apply the merge
	std::list< std::set<Node*> >::iterator setIt;		
	for (setIt  = toMergeSets.begin();
		 setIt != toMergeSets.end();
		 ++setIt)
	{		
		std::set<Node*>& nearNodes = *setIt;
		
		// Compute new coordinates for center
		Node* newNode = Node::createNewAsBarycentre(nearNodes);
		_geoIndex.addToIndex(newNode);
		ioGraph.add(newNode);
		
		// Loop and move linked to new nodes		
		std::set<Node*>::iterator nearNodeIt;
		for (nearNodeIt  = nearNodes.begin();
			 nearNodeIt != nearNodes.end();
			 ++nearNodeIt)  
		{
			_geoIndex.removeFromIndex(*nearNodeIt);
			
			const std::set<Node*>& attachedNodes = ioGraph[*nearNodeIt];
			std::set<Node*>::iterator attachedNodeIt;
			for(attachedNodeIt  = attachedNodes.begin();
				attachedNodeIt != attachedNodes.end();
				++attachedNodeIt)  
			{			
				ioGraph.link(newNode, *attachedNodeIt);

				// Near node will be erased from the connected set when disconnected from all others points
				ioGraph.unlink(*nearNodeIt, *attachedNodeIt);	
			}

			delete *nearNodeIt;			
		}
		
	}
	
	MDW_LOG_DEBUG("Neighbours merged: " << ioGraph.size() << " nodes remaining");
}
////////////////////////////////////////////////////////////////////

bool CmdNodeGraphReduce::geometry_hookNeighbourSegmentToNode(ConnectedSet& ioGraph, 
															  int mergeRadius)
{
	CHRONO("geometry_hookNeighbourSegmentToNode");
	
	//  n-----------------n
	//           N
	//  becomes      
	//     
	//  n---\        /---n
	// 	     ----N---
	
	struct PendingChange
	{
		Node* node1;
		Node* node2;
		std::list< std::pair<Node*, PointF> > toAbsorb;
	};
		
	std::list< PendingChange > pendingChanges;
			
	ConnectedSet::iterator node1It;		
	// - Find a node with neighbours
	for(node1It  = ioGraph.begin();
		node1It != ioGraph.end();
		++node1It)  
	{
		Node* node1 = node1It->first;
	
		// Loop on all segments
		std::set<Node*>::iterator node2It;	
		for(node2It  = node1It->second.begin();
			node2It != node1It->second.end();
			++node2It)
		{	
			Node* node2 = *node2It;
		
			// To avoid processing each node pair twice
			if (node2 <= node1)
				continue;
		
		    // Find near nodes
			std::set<Node*> nearPoints;
			_geoIndex.nearNodes(node1, node2, mergeRadius, nearPoints);
			
			PendingChange aPendingChange;
			// Loop on near nodes
			std::set<Node*>::iterator candidateIt;
			for(candidateIt  = nearPoints.begin();
				candidateIt != nearPoints.end();
				++candidateIt)
			{			
				Node* candidate = *candidateIt;
					
				if (candidate == node1)
					continue;
				
				if (candidate == node2)
					continue;
										
				PointF projected  = Segment(node1, node2).projectionOrthoToSegment(candidate->center());
				if (projected == PointF_Invalid)
					continue;
									
				Node projAsNode(projected);
				float distanceToLine = projAsNode.distance(candidate);

				if (distanceToLine > mergeRadius)
					continue;
					
				//std::cout << "proximity check" << std::endl;
					
				// Do not hook on segments really near
				// TODO express the condition in a smarter way
				if (node1->distance(& projAsNode) < distanceToLine)
					continue;
						
				if (node2->distance(& projAsNode) < distanceToLine)
					continue;		
						
				//MDW_LOG_DEBUG("Candidate for absorption: " << candidate << " - " << *candidate);		
				
				//std::pair<Node*, Node*> thePair = {node1, node2};
				std::pair<Node*, PointF> theAbsorbee = { candidate, projected };
				aPendingChange.toAbsorb.push_back(theAbsorbee);
			}
			
			if (aPendingChange.toAbsorb.empty())
				continue;
			
			aPendingChange.node1 = node1;
			aPendingChange.node2 = node2;
			pendingChanges.push_back(aPendingChange );
		}
		
	}
	
//	if (pendingChanges.empty())
//		return;
	
	int hookedNodesCount = 0;
	
	// Apply changes
	std::list< PendingChange >::iterator pendingChangesIt;
	for(pendingChangesIt  = pendingChanges.begin();
		pendingChangesIt != pendingChanges.end();
		++pendingChangesIt)
	{
		Node* node1 = pendingChangesIt->node1;
		Node* node2 = pendingChangesIt->node2;
		
		std::list< std::pair<Node*, PointF> >::iterator nodeIt;
		for(nodeIt  = pendingChangesIt->toAbsorb.begin();
			nodeIt != pendingChangesIt->toAbsorb.end();
			++nodeIt)
		{
			hookedNodesCount++;
			
			Node* nodeToAbsorb = nodeIt->first;
			PointF projected = nodeIt->second;
			  	
			// Move the node a bit in order to help cnvergence
			// TODO keep the weight of absorbed node
			// TODO update index: remove + re-add
			PointF newCenter;
			newCenter[0] = (nodeToAbsorb->center()[0] + projected[0])/2;
			newCenter[1] = (nodeToAbsorb->center()[1] + projected[1])/2;
			
			_geoIndex.removeFromIndex(nodeToAbsorb);
			nodeToAbsorb->center() = newCenter;	
			_geoIndex.addToIndex(nodeToAbsorb);
			
			// add new segs
			ioGraph.link(node1, nodeToAbsorb);
			ioGraph.link(node2, nodeToAbsorb);
		}		
		
		// remove splitted seg				
		ioGraph.unlink(node1, node2);
	}
	
	MDW_LOG_DEBUG("Line hook on " << pendingChanges.size() << " segments and "<< hookedNodesCount << " points");

	return ! pendingChanges.empty();
}

////////////////////////////////////////////////////////////////////
// 
//    Merge performed if angle < maxAngle OR proj distance < absorbRadius
//
bool CmdNodeGraphReduce::graph_concatConsecutiveSegments(ConnectedSet& ioGraph, float maxAngle, float absorbRadius)
{
	CHRONO("graph_concatConsecutiveSegments");
	
	//  n-----------1 ----------n 
	// becomes
	//  n-----------------------n 
	//  if angle < _maxAngleErrConcat 
	
	int concatSmallAngleCount = 0;
	int concatSmallImpactCount = 0;
	int concatSmallGapCount = 0;				
					
	// Loop on nodes
	ConnectedSet::iterator nodeIt;
	for (nodeIt  = ioGraph.begin();
		 nodeIt != ioGraph.end();
		 )  
	{
		Node* node = nodeIt->first;
		
		if (nodeIt->second.size()!= 2)
		{	++nodeIt; 	continue; 	}
		
		Node* node1 = * nodeIt->second.begin();
		Node* node2 = * nodeIt->second.rbegin();
		Segment seg1(node, node1);
		Segment seg2(node, node2);

		bool doConcat = false;
		
		// Check theta
		float thetaDiff = abs(seg2.theta(node) - seg1.theta(node));
		if (thetaDiff > 360)
			thetaDiff -= 360;

		if (abs(thetaDiff - 180) <  maxAngle)	
		{
			//std::cout << "Concat: flat angle" << std::endl;
			doConcat = true;
			concatSmallAngleCount++;
		}
		
		/*
		if ( !doConcat && onDifferentSides(node, &seg1, &seg2))
		{
			//std::cout << "Concat: alternative method check" << std::endl;
			Segment* small = &seg1;
			Segment* big   = &seg1;
			if (seg2.lenght() > seg1.lenght()) 
				big = &seg2;
			else
				small = &seg2;
				
			if ((small->lenght() / big->lenght()) < 0.1)
			{
				// Check if the new segment will have a similar angle/lenght with the biggest
				Segment test( node1, node2);
				//seg1->otherNode(node)->_segments.push_back(&test);
				//seg2->otherNode(node)->_segments.push_back(&test);
				 
				if (minorAngle(big->otherNode(node), big, &test))
				{
					//std::cout << "ok small impact concat" << std::endl;
					doConcat = true;
					++concatSmallImpactCount;	
				}
			}
		}
		*/
		
		if (!doConcat)
		{
			// Try projection on node1, node2						
			PointF projected  = Segment(node1, node2).projectionOrthoToSegment(node->center());
			if (projected != PointF_Invalid)
			{						
				Node projAsNode(projected);
				float distanceToLine = projAsNode.distance(node);

				if (distanceToLine < absorbRadius)
				{
					doConcat = true;
					concatSmallGapCount++;
				}
			}
		}
		
		if (! doConcat)
		{	++nodeIt; 	continue; 	}
		
		// ok go for concat					
		//Logger::cout() 	<< "Concat: removing " << *node << std::endl;
		//Logger::cout()  << *seg1  << std::endl;
		//Logger::cout()  << *seg2 << std::endl;
		//Logger::cout()  << " into: " << *node << *seg1->otherNode(node) << *seg2->otherNode(node)
		//				<< std::endl;
		
		ioGraph.link(node1, node2);
		
		ioGraph.unlink(node, node1);
		ioGraph.unlink(node, node2);
			
		_geoIndex.removeFromIndex(node);
		delete node;
	}	

	MDW_LOG_DEBUG("Concat applied: " << concatSmallAngleCount << " + "
									<< concatSmallImpactCount << "+" 
									<< concatSmallGapCount  << " nodes removed, " << ioGraph.size() << " remaining." );
									
	return ( concatSmallAngleCount + concatSmallImpactCount + concatSmallGapCount ) != 0;
}

////////////////////////////////////////////////////////////////////

bool CmdNodeGraphReduce::extrapolateLeaves(ConnectedSet& ioGraph, int mergeRadius)
{
	CHRONO("extrapolateLeaves");      
	
	bool someChanges = false;
	 
	//  n----------1   1-----------n 
	// becomes
	//  n------------2-------------n 
	
	//  n-----------1  n-----------n 
	// becomes
	//  n--------------n-----------n 
	  
	// BUT (intersection in merge radius, and extending the leaves)
	//  n-----n
	//          1
	//         / 
	//        /
	//       n   

	// becomes      
	//  n-----n--1
	//          /
	//         / 
	//        /
	//       n
	
	std::set<Node*> excluded;
	
	// Loop on 1-nodes
	ConnectedSet::iterator node1It; 
	// - Group and factorize lines with similar travel      
	for (node1It  = ioGraph.begin();
	     node1It != ioGraph.end();
		 ++node1It)  
	{
		if (node1It->second.size() != 1)
			continue;
	
		Node* node1 = node1It->first;
	   
		// Loop on near segments
		std::set<Node*> nearNodes;
		_geoIndex.nearNodes(node1, mergeRadius, excluded, nearNodes);
		
		std::set<Node*>::iterator node2ItSet;        
		for(node2ItSet  = nearNodes.begin();
			node2ItSet != nearNodes.end();
			++node2ItSet) 
		{
			Node* node2 = *node2ItSet;
			
			if (node1 == node2)
				continue;

			// only merge the leaves together, or a leaf to a CNX3 or more
			// TODO condition Node.isTopologicNode ??
			// leave, or more than 2 segments, or true angle between 2 segments
			ConnectedSet::iterator node2It = ioGraph.find(node2);
			if (node2It->second.size() != 1)
				continue;
					
			// Ok, let's check if those two nodes could be connected
							
			// check segments are looking to each other
			// add epsilon to the leaves and check distance is reduced
			Segment directedSeg1(node1, *node1It->second.begin());
			Segment directedSeg2(node2, *node2It->second.begin());        
					
			Node nodeExt1( node1->center_f() + directedSeg1.normalizedDirVector()); 
			Node nodeExt2( node2->center_f() + directedSeg2.normalizedDirVector()); 
			float distance = node1->distance(node2);
			float distanceAfterExt = nodeExt1.distance(& nodeExt2);         
									
			//MDW_LOG_DEBUG("Distance evolution: " << distance << " to " << distanceAfterExt);              
			if (distanceAfterExt > distance)
				continue;
					
			bool almostFlat = (((int)abs(360 + directedSeg2.theta(node2) - directedSeg1.theta(node1)))%180) < 10 ;
			// if angle is flat, connect
			if (almostFlat)
			{
				MDW_LOG_DEBUG("connecting lonely nodes (flat mode) "  << *node1 << *node2);
				ioGraph.link(node1, node2);
				someChanges = true;
				break;
			}
					
			// Else, add the intersection as a new point only if near
			cv::Point2f intersectionPoint = directedSeg1.intersection(& directedSeg2);
			bool nearIntersection = (Tools::distance(intersectionPoint, node1->center()) < mergeRadius &&
									 Tools::distance(intersectionPoint, node2->center()) < mergeRadius );
			if (!nearIntersection)
				continue;

			MDW_LOG_DEBUG("connecting lonely nodes (intersect mode) "  << *node1 << *node2);
			Node* intersection = new Node(intersectionPoint);
			
			ioGraph.link(intersection, node1);
			ioGraph.link(intersection, node2);
			_geoIndex.addToIndex(intersection);
			someChanges = true;
			break;                          

		}       
			
		++node1It; 
	}
			
	return someChanges;
}
        
////////////////////////////////////////////////////////////////////
// Compenser les derives a cause des merges
bool CmdNodeGraphReduce::realign(ConnectedSet& ioGraph)
{
	//  ----2-     -2--------
	//         -N-

	//  ----2---N---2--------
	//
	
	//const int allowedLevel1Var = 5;
	const int allowedLevel0Var = 20;
	
	// Loop on 2+ -nodes
	ConnectedSet::iterator nodeIt;
	// - Group and factorize lines with similar travel      
	for (nodeIt  = ioGraph.begin();
	     nodeIt != ioGraph.end();
		 ++nodeIt)  
	{
		// Onlt 2+ nodes
		if (nodeIt->second.size() <= 2)
			continue;
		
		bool nodeRealigned = false;
		
		// Find a pair of level2 nodes /tq  
		// seg(lvl2A, lvl2B).dist(lvl0) minimal
		// seg(lvl2A, lvl2B).dist(lvl1A) minimal
		// seg(lvl2A, lvl2B).dist(lvl1B) minimal
		std::set<Node*>::iterator node1ItA, node1ItB;	
		std::set<Node*>::iterator node2ItA, node2ItB;	
		for(node1ItA  = nodeIt->second.begin();
			node1ItA != nodeIt->second.end() && !nodeRealigned;
			++node1ItA)  
		{
			for(node1ItB  = node1ItA;
				node1ItB != nodeIt->second.end() && !nodeRealigned;
				++node1ItB)  
			{
				if (node1ItA == node1ItB)
					continue;
				
				std::set<Node*>& lvl2A = ioGraph[*node1ItA];
				std::set<Node*>& lvl2B = ioGraph[*node1ItB];	
				
				for(node2ItA  = lvl2A.begin();
					node2ItA != lvl2A.end() && !nodeRealigned;
					++node2ItA)  
				{	
					if (*node2ItA == nodeIt->first)
							continue;
						
					for(node2ItB  = lvl2B.begin();
						node2ItB != lvl2B.end() && !nodeRealigned;
						++node2ItB)  
					{	
						if (*node2ItB == nodeIt->first)
							continue;
						
						Segment segment2A(*node2ItA, *node1ItA);
						Segment segment2B(*node2ItB, *node1ItB);
						Segment segment1(*node1ItA, *node1ItB);

						float thetaDiffA = segment2A.theta(*node1ItA) - segment1.theta(*node1ItA);
						if (thetaDiffA < 0)
							thetaDiffA += 360;
							
						float thetaDiffB = segment2B.theta(*node1ItB) - segment1.theta(*node1ItB);
						if (thetaDiffB < 0)
							thetaDiffB += 360;
							
						// Check angles are similar
						if ( abs(thetaDiffA - 180) > 10)
							continue;
						
						if ( abs(thetaDiffB - 180) > 10)
							continue;
						
						
								
						float distance0  = segment1.distanceToSegment(nodeIt->first);
						
						if (distance0 > allowedLevel0Var)
							continue;
						
						MDW_LOG_DEBUG("Node realignement");
						PointF newCoord = segment1.projectionOrthoToLine(nodeIt->first);
						
						_geoIndex.removeFromIndex(nodeIt->first);
						nodeIt->first->center() = newCoord;
						_geoIndex.addToIndex(nodeIt->first);

						nodeRealigned = true;
					}
				}
			}
		}
		
	}
	return true;
}
        
////////////////////////////////////////////////////////////////////

bool CmdNodeGraphReduce::onDifferentSides(Node* iNode, Segment* iSeg1, Segment* iSeg2)
{
	int smallDiffThreshold = 10; // TODO should vary on image resolution?
	
	PointF point = iNode->center_f();
	PointF point1 = iSeg1->otherNode(iNode)->center_f();
	PointF point2 = iSeg2->otherNode(iNode)->center_f();	
	
	bool x_onDiffSides = (point[0] - point1[0])* (point[0] - point2[0]) < 0; 
	bool y_onDiffSides = (point[1] - point1[1])* (point[1] - point2[1]) < 0;
	
	bool x_smallDiff = abs(point[0] - point1[0]) < smallDiffThreshold 
					&& abs(point[0] - point2[0]) < smallDiffThreshold;
	bool y_smallDiff = abs(point[1] - point1[1]) < smallDiffThreshold 
					&& abs(point[1] - point2[1]) < smallDiffThreshold;
		
	if ((x_onDiffSides || x_smallDiff) 
	 && (y_onDiffSides || y_smallDiff))
		return true;
		
	return false;				
}

////////////////////////////////////////////////////////////////////

bool CmdNodeGraphReduce::flatAngle(Node* iNode, Segment* iSeg1, Segment* iSeg2)
{
	// Check theta
	float thetaDiff = abs(iSeg2->theta(iNode) - iSeg1->theta(iNode));
	if (thetaDiff > 360)
		thetaDiff -= 360;

	if (abs(thetaDiff - 180) >  _parameters._maxAngleErr)	
		return false;

	return true;				
}

///////////////////////////////////////////////////////////////////////

bool CmdNodeGraphReduce::minorAngle(Node* iNode, Segment* iSeg1, Segment* iSeg2)
{
	// Check theta
	float thetaDiff = abs(iSeg2->theta(iNode) - iSeg1->theta(iNode));
	if (thetaDiff > 360)
		thetaDiff -= 360;
		
	if (abs(thetaDiff) >  _parameters._maxAngleErr)	
		return false;

	return true;				
}

