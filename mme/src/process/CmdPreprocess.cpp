
#include "CmdPreprocess.hpp"


#include "QueryContext.hpp"
#include "Parameters.hpp"

#include "toolbox/Logger.hpp"

#include "Geometry.hpp"
#include "Color.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#define DEBUG_HOUGH MDW_LOG_DEBUG

/////////////////////////////////////////////////////////////////////

void CmdPreprocess::execute(QueryContext& iContext,
								 PointMatrix& ioOut)
{	
	PointMatrix src = iContext.getSourceImage().clone();	

	// Convert to grayscale
	{
		MDW_LOG_CONTEXT("GrayscaleConversion");
		cvtColor(src, ioOut, CV_BGR2GRAY);
#ifdef DEBUG_HOUGH	
		iContext.log(ioOut);
#endif
	}

	// Apply blur to smooth edges and use adapative thresholding    
	{
		MDW_LOG_CONTEXT("GaussianBlur");	
		cv::GaussianBlur(ioOut, ioOut, cv::Size(9,9), 50, 50 );  
#ifdef DEBUG_HOUGH	
		iContext.log(ioOut);
#endif
	}
 	
 	{
		MDW_LOG_CONTEXT("AdaptiveThresholding");
		cv::adaptiveThreshold(ioOut, ioOut, 
							255, 
							CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY ,
							49 , // 75 block size
							10   // 10 mean shift
							);  
#ifdef DEBUG_HOUGH	
		iContext.log(ioOut);
#endif
	}

 	// Thresholding
 	{
		MDW_LOG_CONTEXT("Thresholding");
		cv::threshold(ioOut, ioOut, 127, 255, cv::THRESH_BINARY);	
#ifdef DEBUG_HOUGH	
		iContext.log(ioOut);
#endif
	}
	/*
	// Invert image
	{
		MDW_LOG_CONTEXT("Bitwise_not");	
		cv::bitwise_not(ioOut, ioOut);   
#ifdef DEBUG_HOUGH
		iContext.log(ioOut);
#endif
	}
 	*/
 	
 	// Apply the erosion operation	
 	int erosionCount = 0;
    {
		MDW_LOG_CONTEXT("ImageErosion");
			 
		bool done;		
		do
		{
			erosionCount++;
			MDW_LOG_DEBUG("erosion loop "<< erosionCount);
			int changed = erode(ioOut);
			
#ifdef DEBUG_HOUGH	
		iContext.log(ioOut);
#endif
			MDW_LOG_DEBUG("erosion loop "<< erosionCount << " modif count =" << changed);
			 
			done = (changed < 10);
		} while (!done);
    }
 
 /*
	{
		int allPointsCount = iContext.getParameters()._hRes* iContext.getParameters()._vRes;
		int skelPointsCount = allPointsCount - cv::countNonZero(ioOut);
		MDW_LOG_DEBUG("Skeleton with " << skelPointsCount << " points (" << ((float)100* skelPointsCount) / allPointsCount << ")");	
	}	
*/
#ifdef DEBUG_HOUGH	
		iContext.log(ioOut);
#endif

	return;
}

////////////////////////////////////////////////////////////////////

bool nodeCanBeEroded(int mainIndex, int cols, U8* data, U8* data2)
{
	// Remove this px only if one color change around (eg one contigus white set + one contigus black set)
	int blackNeighboursCount = 0;		
	int colorSwitchCount = 0;
	bool currentIsBlack = data[mainIndex - cols -1] < Grayscale::Gray;
			
#define MME_CHECK_POINT(x)\
	{\
		bool nodeIsBlack = data[x] < Grayscale::Gray && data2[x] < Grayscale::Gray;\
		colorSwitchCount += (nodeIsBlack ^ currentIsBlack);\
		blackNeighboursCount += nodeIsBlack? 1 : 0;\
		currentIsBlack = nodeIsBlack;\
	}
	
	MME_CHECK_POINT(mainIndex - cols); // NORTH
	MME_CHECK_POINT(mainIndex - cols +1); 
	MME_CHECK_POINT(mainIndex + 1);    // EAST
	MME_CHECK_POINT(mainIndex + cols +1);
	MME_CHECK_POINT(mainIndex + cols); // SOUTH
	MME_CHECK_POINT(mainIndex + cols -1);
	MME_CHECK_POINT(mainIndex - 1);    // WEST
	MME_CHECK_POINT(mainIndex - cols -1);
#undef MME_CHECK_POINT			
	
	// isolated points
	if (blackNeighboursCount == 0)
		return true;
	
	// Do a specific case for those ones ?
	if (blackNeighboursCount == 1 && data == data2)
		return false;	
				
	if (blackNeighboursCount >= 7)
		return false;
		
	if (colorSwitchCount != 2)
		return false;	

	return true;	
}

/////////////////////////////////////////////////////////////////////

int CmdPreprocess::erode(PointMatrix& img)
{
	// o o x
	// o X x
	// o o x
	
	// o x x mais pas o x o
	// o X x          o x o
	// o x x          o x o
	
	// x x x mais pas x o o 
	// o X x          o x o
	// o o x          o o x

	// suppression si au moins 3 voisins noirs
	int changed = 0;

	int rows = img.rows;
	int cols = img.cols;
	int border = 2; // on va pas se faire chier pour 2 px
	
	PointMatrix pendingUpd = cv::Mat::zeros(rows, cols, CV_8U);
	
	// Internally stored a BGR
	unsigned char* data = img.data;
	
    for (int rowIdx = border; rowIdx < rows - border; ++rowIdx)  
    {  
		for (int colIdx = border; colIdx < cols - border; ++colIdx)  
		{			  			
			int mainIndex = rowIdx*cols + colIdx;
			
			// Skip white points
			if (data[mainIndex] > Grayscale::Gray)
				continue;
					
			if (! nodeCanBeEroded(mainIndex, cols, data, data))
				continue;
				
			// Check it's also ok when taking pending changes into account
			if (! nodeCanBeEroded(mainIndex, cols, data, pendingUpd.data))
				continue;
			
			pendingUpd.data[mainIndex] = Grayscale::White;
			++changed;
		}
	}	
	
	// Apply pending changes
	img += pendingUpd;
	
	return changed;
}

