#pragma once

#include <vector>

#include "Geometry.hpp"

namespace cv
{
	class Mat;
}

class QueryContext;

class CmdPreprocess
{
	public:

		static void execute (QueryContext& iContext, PointMatrix& ioOut);
		
		
		static int erode(PointMatrix& img);	
};




