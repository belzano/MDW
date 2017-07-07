#include "Parameters.hpp"

#include "toolbox/StringUtils.hpp"

#include <iostream>
#include "Geometry.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

void Parameters::init(const PointMatrix& img)
{
	//_sourceName = iFilename;
	_sourceImage = img.clone();
	
	// Retrieving img characteristics
	_vRes = img.rows;
	_hRes = img.cols;
	int imgRes = _vRes * _hRes;
	_refRes = sqrt(_vRes*_hRes);

 	// Parameters about lines detection
	//////////////////////////////////////////
	// rho : The resolution of the parameter r in pixels. We use 1 pixel.		
	_HoughLinesParameters.resolution = 1;
	// theta: The resolution of the parameter theta in radians. We use 1 degree (CV_PI/180)
	_HoughLinesParameters.theta = CV_PI/180;
	// threshold: The minimum number of intersections to “detect” a line
	_HoughLinesParameters.threshold = 0.01 * _refRes; // 1 % of reference size;
	// minLinLength: The minimum number of points that can form a line. 
	_HoughLinesParameters.minLineLenght = 0.02 * _refRes; // 2 % of reference size;
	// maxLineGap: The maximum gap between two points to be considered in the same line.
	_HoughLinesParameters.maxLineGap = 0.005 * _refRes; // 0.5 % of reference size


	_lineThickness = 10;
/*
	_nodeMergeRadius 				= 2* _lineThickness;
	_lineHookRadius					= 2* _lineThickness;
	_nodeMergeRadius_LineAbsorption = 1* _lineThickness;
	_leafSegmentsConnectionMaxGap   = 5* _lineThickness;
	_maxAngleErr = 10;	 
	_maxAngleErrConcat = 2;
*/

	_nodeMergeRadius 				= 3 + 0.005* _refRes; // 0.5 % of reference size;
	_lineHookRadius					= 3 + 0.005* _refRes;// 0.5% of reference size;
	_nodeMergeRadius_LineAbsorption = 3 + 0.005* _refRes; // 0.5 % of reference size;
	_leafSegmentsConnectionMaxGap   = 3 + 0.01 * _refRes; // 1 % of reference size;
	_maxAngleErr = 1;	 
	_maxAngleErrConcat = 2;
		 
		 
 	// Parameters about shapes filtering
	//////////////////////////////////////////
	// Skip polygons if area < 1 %
	_shapeMinArea = 0.01 * imgRes;
	// Skip polygons if area > 90 %
	_shapeMaxArea = 0.90 * imgRes;			 
 			
 	// Debug drawings params
 	_debugDrawResolution = 1 ;//+ ((float)imgRes*0.005);	
 	_penWidth 			 = 1 ;//+ ((float)_refRes*0.001);
 
}
