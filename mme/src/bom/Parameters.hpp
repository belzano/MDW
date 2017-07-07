#pragma once

#include <iostream>
#include <string>

#include "Geometry.hpp"

using namespace std;

class Parameters
{
	public:
 
	void init (const PointMatrix& img);
		
	// general parameters
	int _vRes, _hRes;
	float _refRes; 
	
	//std::string _sourceName;
	PointMatrix	   _sourceImage;
	
	
	// Parameters about preprocesing
	
	
	
	// Parameters about line detection
	struct HoughLinesParameters
	{
		int resolution;
		float theta;
		int threshold;
		int minLineLenght;
		int maxLineGap;
	};
	HoughLinesParameters _HoughLinesParameters;
	
	
	// Parameters about graph construction / reduction
	float _lineThickness;
	
	float _nodeMergeRadius;
	float _lineHookRadius;
	float _nodeMergeRadius_LineAbsorption;
	float _leafSegmentsConnectionMaxGap;
	
	float _maxAngleErr;
	float _maxAngleErrConcat;
	
	// 
	int _shapeConnectivity;
	
	
	// Parameters about shapes filtering
	int _shapeMinArea;
	int _shapeMaxArea;
	
	// debug
	int _debugDrawResolution;
	int _penWidth;
};




