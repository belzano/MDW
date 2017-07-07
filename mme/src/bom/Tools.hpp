#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

#include "Geometry.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////

class Tools
{
	public:
	
	static float distance(PointI a, PointI b);
	
	//static float distance(PointF a, PointF b);
	static float distance(const PointF& a, const PointF& b);	
	
	static float theta(LineI line);
	static float curveRadius(const PointF& a, const PointF& b, const PointF& c);
};
//////////////////////////////////////////////////////////////////


