#include "ConnectedSetStats.hpp"
#include "ConnectedSet.hpp"

#include "Node.hpp"
#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void EnclosingRectangleStats::compute(const ConnectedSet& iSet)
{ 
	_enclosingRectMin = iSet.begin()->first->center_f();
	_enclosingRectMax = iSet.begin()->first->center_f();
		
	for(ConnectedSet::const_iterator aNodeIt  = iSet.begin();
		aNodeIt != iSet.end();
		++aNodeIt)
	{
		PointF center = aNodeIt->first->center_f();
		
		if (center[0] < _enclosingRectMin[0])
			_enclosingRectMin[0] = center[0];
		if (center[0] > _enclosingRectMax[0])
			_enclosingRectMax[0] = center[0];	
		if (center[1] < _enclosingRectMin[1])
			_enclosingRectMin[1] = center[1];
		if (center[1] > _enclosingRectMax[1])
			_enclosingRectMax[1] = center[1];	
	}
}

////////////////////////////////////////////////////////////////////

PointF EnclosingRectangleStats::getEnclosingRectCenter() const
{
	PointF center;
	center[0] = (_enclosingRectMin[0] + _enclosingRectMax[0])/2;
	center[1] = (_enclosingRectMin[1] + _enclosingRectMax[1])/2;
	return center;	
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void WalkedAngleStats::compute(const ConnectedSet& iSet)
{
	_walkedAngles.clear();
	
	ConnectedSet::const_iterator theIt = iSet.begin();	
	Node* currentNode  = theIt->first;
	Node* previousNode = *theIt->second.rbegin();
	Node* nextNode     = *theIt->second.begin();
	
	for (;true;)
	{
		float angularVariation = 0;	
		
		Segment fromSeg(previousNode, currentNode);
		Segment toSeg(currentNode, nextNode);
		angularVariation = toSeg.theta(currentNode) - fromSeg.theta(previousNode);
		if (angularVariation < -180)
			angularVariation += 360;
		if (angularVariation > 180)
			angularVariation -= 360;
		
		_walkedAngles.push_back(angularVariation);	
		
		previousNode = currentNode;
		currentNode = nextNode;
		nextNode = *iSet.find(currentNode)->second.begin();
		if (nextNode == previousNode)
			nextNode = *iSet.find(currentNode)->second.rbegin();
			
		if (iSet.find(currentNode) == theIt)
			break;
	}
}

///////////////////////////////////////////////////////////////////

int WalkedAngleStats::getNumberOfEdges() const
{
	// Compute angles
	/////////////////////////////////////////////	
	float sumAngles = 0;
	float sumAnglesWithoutFlat = 0;
	
	std::list<float>::const_iterator angleIt;
	for(angleIt  = _walkedAngles.begin();
		angleIt != _walkedAngles.end();
		++angleIt)
	{
		float angle = *angleIt;
		
		sumAngles += angle;
		
		// Skip flat angles
		if (abs(angle - 180) < 20)
			continue;
		
		sumAnglesWithoutFlat += angle;
	}
	
	// number of edges
	return (abs(sumAngles)/180) + 2;	
}

////////////////////////////////////////////////////////////////////

bool WalkedAngleStats::isConnex() const
{
	if (_walkedAngles.empty())
		return false;
	
	int orientationChangeCount = 0;
	float previousAngle = 0;
	//std::string angles; 	
	std::list<float>::const_iterator angleIt;	
	for(angleIt  = _walkedAngles.begin();
		angleIt != _walkedAngles.end();
		++angleIt)
	{
		if (angleIt != _walkedAngles.begin())
		{
			if (abs(previousAngle) < 20)
				previousAngle = 0;
				
			if (previousAngle * *angleIt < 0)
				orientationChangeCount++;
		}	
		previousAngle = *angleIt;
		
		// Debug stuff
		//angles += toolbox::ToString(*angleIt);
		//angles += ", ";
	}
	orientationChangeCount /= 2;
	
	//MDW_LOG_DEBUG("Walked angles: " << angles);
	return orientationChangeCount <= 4;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void ProfileStats::compute(const ConnectedSet& iSet)
{ 
	_graphProfile.clear();

	for(ConnectedSet::const_iterator aNodeIt  = iSet.begin();
		aNodeIt != iSet.end();
		++aNodeIt)
	{
		_graphProfile[aNodeIt->second.size()] += 1;
	}		

	_nodeCount = iSet.size();
}

/////////////////////////////////////////////////////////////////

const std::map<int, int>& ProfileStats::getProfile() const
{
	return _graphProfile;
}

////////////////////////////////////////////////////////////////////

bool ProfileStats::isClosed() const
{	
	// Check only cnx 2
	return  (_nodeCount > 2)
		&&	(_graphProfile.size() == 1) 
		&&  (_graphProfile.find(2) != _graphProfile.end());
}

////////////////////////////////////////////////////////////////////

bool ProfileStats::isCloseable() const
{
	// Check only cnx 1 and 2
	return  (_nodeCount > 2)
		&&	(_graphProfile.size() <= 2) 
		&&  (_graphProfile.rbegin()->first == 2); 
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void GravityCenterStats::compute(const ConnectedSet& iSet)
{ 
	computeCenter(iSet);
	computeOthersMetrics(iSet);
}

////////////////////////////////////////////////////////////////////

void GravityCenterStats::computeCenter(const ConnectedSet& iSet)
{ 
	_gravityCenter[0] = 0; 
	_gravityCenter[1] = 0; 


	int weight = 0;
	for(ConnectedSet::const_iterator aNodeIt  = iSet.begin();
		aNodeIt != iSet.end();
		++aNodeIt)
	{
		//int nodeWeight = 0;
		for(std::set<Node*>::const_iterator aNode2It  = aNodeIt->second.begin();
			aNode2It != aNodeIt->second.end();
			++aNode2It)
		{
			float nodeWeight = aNodeIt->first->distance(*aNode2It);
		
			PointF center = aNodeIt->first->center_f();
			_gravityCenter[0] += nodeWeight * center[0];
			_gravityCenter[1] += nodeWeight * center[1];
			
			weight += nodeWeight;
		}		
	}
		
	_gravityCenter[0] /= weight;
	_gravityCenter[1] /= weight;
}
	
///////////////////////////////////////////////////////////////////

void GravityCenterStats::computeOthersMetrics(const ConnectedSet& iSet)
{
	_sortedDistanceFromGravCenter.clear();
	_avgDistanceFromGravCenter = 0;
	
	ConnectedSet::const_iterator theIt;	
	for(theIt  = iSet.begin();
		theIt != iSet.end();
		++theIt)  
	{
		Node* currentNode = theIt->first;
		float distFromGrav = Tools::distance( _gravityCenter, currentNode->center_f());
		_avgDistanceFromGravCenter += distFromGrav;
		_sortedDistanceFromGravCenter.insert( { distFromGrav, currentNode} );
	}	
	_avgDistanceFromGravCenter /= iSet.size();
}

///////////////////////////////////////////////////////////////////

const PointF& GravityCenterStats::getGravityCenter() const
{
	return _gravityCenter;	
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void CentralAngleStats::compute(const ConnectedSet& iSet, const PointF& center) 
{
	std::list<std::pair<float, Node*>> _slicesFromGravAngles;
	CentralAngleStats::sliceAngles(iSet, center, _slicesFromGravAngles);
	
	bool allPositive = true;
		
	//std::cout << " slice from gravity angles: ";
		
	std::list<std::pair<float, Node*>>::iterator angleIt;
	for(angleIt  = _slicesFromGravAngles.begin();
		angleIt != _slicesFromGravAngles.end();
		++angleIt)
	{
		if (angleIt->first < 0 || angleIt->first > 180)
			allPositive = false;
		
		//std::cout << angleIt->first << "; ";	
	}
	//std::cout << std::endl;
		
	_isPerimeterBacktracking = !allPositive;
}

////////////////////////////////////////////////////////////////////

void CentralAngleStats::sliceAngles(const ConnectedSet& iSet,
									const PointF& center, 
									std::list< std::pair<float, Node*> >& oAngles) const
{
	// NB:
	// Algo can only process shapes:
	// - with only CNX-2 (closed set)
	// - with only CNX-2 and 2 CNX-1 (closed set)
	
	Node gravCenter = Node(center);
	
	ConnectedSet::const_iterator theIt = iSet.begin();	
	Node* currentNode  = theIt->first;
	Node* previousNode = *theIt->second.begin();
	Node* nextNode     = *theIt->second.rbegin();
	
	{
		Segment prevSegment(&gravCenter, currentNode);
		Segment nextSegment(&gravCenter, nextNode);
		
		float initAngle = prevSegment.theta(&gravCenter) - nextSegment.theta(&gravCenter);
		//std::cout << "Computed init: " << initAngle << std::endl;
		if (initAngle < 0)
			initAngle += 360;
			
		if (initAngle > 180)
		{
			if (theIt->second.size() != 2)
			{
				MDW_LOG_ERROR("Potential logical error here");
			}
			nextNode = *theIt->second.begin();
			previousNode = *(++(theIt->second.begin()));	
		}
	}

	for(;;)  
	{
		Segment prevSegment(&gravCenter, currentNode);
		Segment nextSegment(&gravCenter, nextNode);
		
		//MDW_LOG_DEBUG("Slice formed by" << prevSegment << " - " << nextSegment );
		
		float theta = prevSegment.theta(&gravCenter) - nextSegment.theta(&gravCenter);
		
		//std::cout << "Computed angle: " << theta << std::endl;
		
		if (theta < 0)
			theta += 360;
			
		oAngles.push_back( { theta, nextNode });

		
		// Next loop
		previousNode = currentNode;
		currentNode  = nextNode;	
		theIt = iSet.find(currentNode);
		
		if (theIt->second.size() != 2)
		{
			MDW_LOG_ERROR("Potential logical error here");
		}
		
		nextNode     =  *theIt->second.begin();
		if(nextNode == previousNode)
			nextNode     =  *(++theIt->second.begin());
			
		if (currentNode == iSet.begin()->first)
			break;
	}	
	
}

////////////////////////////////////////////////////////////////////

bool CentralAngleStats::isPerimeterBacktracking() const 
{
	return _isPerimeterBacktracking;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void ConnectedSetStats::compute(const ConnectedSet& iSet)
{ 
	ProfileStats::compute(iSet);
	EnclosingRectangleStats::compute(iSet);
	GravityCenterStats::compute(iSet);
		
	if (! ProfileStats::isClosed())
		return;
	
	// TODO this only has sense if only CNX 1 and 2
	WalkedAngleStats::compute(iSet);
	
	CentralAngleStats::compute(iSet, getGravityCenter());
	
	/*
	// Compute statistics on the shape - closed shape part	
	/////////////////////////////////////////////
	_sortedAngles.clear();
	_sortedAnglesAbs.clear();
	//_sortedCurveRadius.clear();
	//_sortedLenghts.clear();
		
	ConnectedSet::const_iterator theIt = iSet.begin();	
	Node* currentNode  = theIt->first;
	Node* previousNode = *theIt->second.begin();
	Node* nextNode     = *(++theIt->second.begin());
	
	{
		Segment prevSegment(previousNode, currentNode);
		Segment nextSegment(currentNode, nextNode);
		
		float initAngle = prevSegment.theta(previousNode) - nextSegment.theta(currentNode);
		if (initAngle < 0)
			initAngle += 360;
		initAngle = 180 - initAngle;
 
		//std::cout << "Initial angle: " << initAngle << std::endl;			
		
		// Loop inside the shape
		if ( abs(initAngle) > 180 )
		{
			nextNode = *theIt->second.begin();
			previousNode = *(++theIt->second.begin());	
		}
	}

	for(;;)  
	{
		Segment prevSegment(previousNode, currentNode);
		Segment nextSegment(currentNode, nextNode);
		
		float theta = prevSegment.theta(previousNode) - nextSegment.theta(currentNode);
		if (theta < 0)
			theta += 360;
		theta = 180 - theta;
		
		//std::cout << "Computed angle: " << theta << std::endl;
	
		//std::multimap<float, Node*>
		_sortedAngles.insert( {theta, currentNode} );
		_sortedAnglesAbs.insert( { abs(theta), currentNode } );
		//std::multimap<float, Node*> 					
		//_sortedCurveRadius.insert( { theta, currentNode } );
		//std::multimap<float, Segment* > 
		//_sortedLenghts.insert(
		//	{Tools::distance(previousNode->center_f(),currentNode->center_f()), 
		//	 {previousNode,currentNode}} );
		
		// Next loop
		previousNode = currentNode;
		currentNode  = nextNode;	
		theIt = iSet.find(currentNode);
		nextNode     =  *theIt->second.begin();
		if(nextNode == previousNode)
			nextNode     =  *(++theIt->second.begin());
			
		if (currentNode == iSet.begin()->first)
			break;
	}	
		*/
}

