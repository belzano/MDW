#pragma once

#include <list>

#include <iostream>
#include "Geometry.hpp"

using namespace std;

class Node;

//////////////////////////////////////////////////////////////////

class SegmentLight
{
	public:
		SegmentLight(Node* iNode1, Node* iNode2);
		
		cv::Point2f intersection(SegmentLight* iOther);
				
		Node* 		_zone1;
		Node* 		_zone2;
		
		float 		coef_a() const;
		float 		coef_b() const;

		PointF 		normalizedDirVector() const;

		float 		distanceToSegment(const Node* iNode) const;
		float 		distanceToSegment(PointF iPoint) const;
		
		float 		distanceToLine(const Node* iNode) const;
		float 		distanceToLine(PointF iPoint) const;
		
		// Projection on the segment. returns (-1, -1) if no projection
		PointF 		projectionOrthoToSegment(Node* iNode) const;
		PointF 		projectionOrthoToSegment(PointF iPoint) const;
			
		PointF 		projectionOrthoToLine(PointF iPoint) const;	
		PointF 		projectionOrthoToLine(Node* iNode) const;
		
		Node* 		otherNode(Node*);
		
		float 		theta(Node* node = NULL) const;
		float 		lenght() const;
		
};

class Segment : public SegmentLight
{
	public:
		Segment(Node* iNode1, Node* iNode2)
			 : SegmentLight(iNode1, iNode2) {}
	
	std::ostream& toStream(std::ostream& ioStream);		 
};

//////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& ioStream, Segment& iSegment);



