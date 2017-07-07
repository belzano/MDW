#include "Tools.hpp"
#include <ctime>

float distanceWithCache(double xa, double ya, double xb, double yb)
{
	return sqrtf( (xb-xa)*(xb-xa) + (yb-ya)*(yb-ya) );
}

////////////////////////////////////////////////////////////////////

float Tools::distance(PointI b, PointI a)  
{
	return sqrtf( (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) );
}

////////////////////////////////////////////////////////////////////

float Tools::distance(const PointF& b, const PointF& a)  
{
	return sqrtf( (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) );
}

////////////////////////////////////////////////////////////////////

float Tools::theta(LineI line)  
{
	float length = distance( PointI(line[0], line[1]),
							 PointI(line[2], line[3]));					 
	float aTheta = acosf(((float)(line[3] - line[1])) / length );	
	return aTheta * 180 / CV_PI;
}

////////////////////////////////////////////////////////////////

float Tools::curveRadius(const PointF& a, const PointF& b, const PointF& c)
{
	float x1 = a[0];
	float y1 = a[1];
	
	float x2 = b[0];
	float y2 = b[1];
	
	float x3 = c[0];
	float y3 = c[1];
	
	float diff12 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
	float diff13 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1);
	float diff32 = (x2-x3)*(x2-x3) + (y2-y3)*(y2-y3);

	int denom = 2 * abs(x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y1 - x1*y3);
	
	return sqrtf(diff12 * diff13 * diff32) / denom;
}
