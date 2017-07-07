
#include "Segment.hpp"

#include "Node.hpp"

#include <iostream>
#include <exception>

#include "Geometry.hpp"

using namespace std;

SegmentLight::SegmentLight(Node* iNode1, Node* iNode2): 
						_zone1(iNode1),
						_zone2(iNode2)
{
	if (iNode1 == iNode2)
		throw std::exception();
		
	//if (iNode1->center_i() == iNode2->center_i())
	//	throw std::exception("0 SegmentLight");
}

////////////////////////////////////////////////////////////////////

float SegmentLight::coef_a() const
{
	float y_diff = _zone2->center()[1] - _zone1->center()[1];
	float x_diff = _zone2->center()[0] - _zone1->center()[0];
		
	return (y_diff / x_diff); 
}

////////////////////////////////////////////////////////////////////

float SegmentLight::coef_b() const
{
	float num = _zone2->center()[0] * _zone1->center()[1]
			  - _zone1->center()[0] * _zone2->center()[1];
	float x_diff = _zone2->center()[0] - _zone1->center()[0];	
	
	return (num / x_diff);
}

////////////////////////////////////////////////////////////////////

float SegmentLight::distanceToSegment(const Node* iPoint) const
{
	return distanceToSegment(iPoint->center_f());
}

////////////////////////////////////////////////////////////////////

float SegmentLight::distanceToSegment(PointF iPoint) const
{
	PointF proj = projectionOrthoToSegment(iPoint);
	if (proj == PointF_Invalid)
	{
		return std::min<float>(Tools::distance(iPoint, _zone1->center_f()),
							   Tools::distance(iPoint, _zone2->center_f()));
	}
	
	return Tools::distance(iPoint, proj);
}


////////////////////////////////////////////////////////////////////

float SegmentLight::distanceToLine(const Node* iPoint) const
{
	return distanceToLine(iPoint->center_f());
}

////////////////////////////////////////////////////////////////////

float SegmentLight::distanceToLine(PointF iPoint) const
{
	PointF proj = projectionOrthoToLine(iPoint);	
	return Tools::distance(iPoint, proj);
}

////////////////////////////////////////////////////////////////////

PointF SegmentLight::projectionOrthoToSegment(Node* iNode) const
{
	return projectionOrthoToSegment(iNode->center_f());
}

////////////////////////////////////////////////////////////////////

PointF SegmentLight::projectionOrthoToSegment(PointF iPoint) const
{	
	PointF projected = projectionOrthoToLine(iPoint);
		
	if ((projected[0] - _zone1->center()[0]) * (projected[0] - _zone2->center()[0]) > 0)
		return PointF_Invalid;
										
	if ((projected[1] - _zone1->center()[1]) * (projected[1] - _zone2->center()[1]) > 0)
		return PointF_Invalid;
	
	return projected;			
}

////////////////////////////////////////////////////////////////////

PointF SegmentLight::projectionOrthoToLine(Node* iNode) const
{
	return SegmentLight::projectionOrthoToLine(iNode->center_f());
}

////////////////////////////////////////////////////////////////////

PointF SegmentLight::projectionOrthoToLine(PointF iPoint) const
{	
	PointF proj;
	PointF vec = normalizedDirVector();
	
	// vertical line. x = 5
	if (vec[0] == 0)
		{
		proj[0] = _zone1->center_f()[0];
		proj[1] = iPoint[1];
		return proj;
	}
	
	// horizontal line. y = 2
	if (vec[1] == 0)
	{
		proj[0] = iPoint[0];
		proj[1] = _zone1->center_f()[1];
		return proj;
	}
	
	float a = coef_a();
	float b = coef_b();
	
	float c = -1/a;
	float d = iPoint[1] - c* iPoint[0]; // d=y-cx
	
	proj[0] = (d-b)/(a-c);
	proj[1] = c*proj[0] + d;
	return proj;
}

////////////////////////////////////////////////////////////////////

PointF SegmentLight::normalizedDirVector() const
{
	PointF vec;
	float lenght = SegmentLight::lenght();
	vec[0] = (_zone1->center()[0] - _zone2->center()[0]) / lenght;
	vec[1] = (_zone1->center()[1] - _zone2->center()[1]) / lenght;
	return vec;
}

////////////////////////////////////////////////////////////////////

float SegmentLight::theta(Node* node) const
{				 
	PointF vec = normalizedDirVector();
	
	float cosinus = vec[0];
	float sinus   = vec[1];
	
	if (node == _zone2)
	{
		cosinus = - cosinus;
		sinus = - sinus;
	}
	
	if (cosinus <= -1)
		return 180; 
	if (cosinus >= 1)
		return 0;
		
	float aTheta = 0;
	
	if  (sinus >= 0)
		aTheta =  acosf(cosinus);
	else  //(sinus < 0)
		aTheta = CV_PI + acosf(-cosinus);
		
	return aTheta * 180 / CV_PI;
}

////////////////////////////////////////////////////////////////////

float SegmentLight::lenght() const
{
	return _zone1->distance(_zone2);
}

/////////////////////////////////////////////////////////////////////
		
cv::Point2f SegmentLight::intersection(SegmentLight* iOther)  
{  
	int threshold = 100000;
	
	int x1 = _zone1->center()[0], y1 = _zone1->center()[1];
	int x2 = _zone2->center()[0], y2 = _zone2->center()[1];
	int x3 = iOther->_zone1->center()[0], y3 = iOther->_zone1->center()[1];
	int x4 = iOther->_zone2->center()[0], y4 = iOther->_zone2->center()[1];
     
	float d = ((float)(x1-x2) * (y3-y4)) - ((y1-y2) * (x3-x4));
	
	if (d != 0)  
	{  
		cv::Point2f pt;  
		pt.x = ((x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4)) / d;  
		pt.y = ((x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4)) / d;  
   
        //-10 is a threshold, the POI can be off by at most 10 pixels
        if(	pt.x < min(x1,x2)-threshold||
			pt.x > max(x1,x2)+threshold||
			pt.y < min(y1,y2)-threshold||
			pt.y > max(y1,y2)+threshold)
        {  
			return cv::Point2f(-1,-1);  
        }  
        
        if( pt.x < min(x3,x4)-threshold||
			pt.x > max(x3,x4)+threshold||
			pt.y < min(y3,y4)-threshold||
			pt.y > max(y3,y4)+threshold)
        {  
            return cv::Point2f(-1,-1);  
        }  
		return pt;  
	}  
	else  
		return cv::Point2f(-1, -1);  
 }

////////////////////////////////////////////////////////////////////

Node* SegmentLight::otherNode(Node* iNode)
{
	if (_zone1 == iNode)
		return _zone2;
		
	if (_zone2 == iNode)
		return _zone1;
	
	std::cout 	<< "About to throw; zone not found. (" << iNode << ") "
				<< _zone1 << " - " << _zone2 << std::endl;
	
	throw std::exception();
}

////////////////////////////////////////////////////////////////////

std::ostream& Segment::toStream(std::ostream& ioStream)
{ 
	ioStream 	<< *_zone1 << " -> " << *_zone2
				<< " theta " << theta() 
				<< ", vec=(" << normalizedDirVector()[0] << ","
				<< normalizedDirVector()[1] << ")";
	return ioStream;
}

std::ostream& operator<<(std::ostream& ioStream, Segment& iSegmentLight)
{
	return iSegmentLight.toStream(ioStream);
}
