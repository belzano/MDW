#pragma once

#include "toolbox/Types.hpp"
#include "opencv2/highgui/highgui.hpp"

typedef cv::Vec2f PointF;
typedef cv::Vec2i PointI;

typedef cv::Vec4i LineI;
	
typedef	cv::Mat	PointMatrix;

static PointF PointF_Invalid = PointF(-1, -1);
static PointI PointI_Invalid = PointI(-1, -1);
