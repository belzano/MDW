#include "QueryContext.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/Logger.hpp"

#include "ApplicationConfig.hpp"

#include <iostream> 
#include <iterator>
#include <vector>
#include <time.h>

#include "Geometry.hpp"
#include "Color.hpp"

#include "Node.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"

using namespace std;



////////////////////////////////////////////////////////////////////

void drawPoint(PointMatrix& copy, const PointF& point, const cv::Scalar& color, int penWidth)
{
	cv::line(copy, 
				cv::Point(point[0]+2, point[1]+2),
				cv::Point(point[0]-2, point[1]-2),
				color, penWidth );
				
	cv::line(copy, 
				cv::Point(point[0]+2, point[1]-2),
				cv::Point(point[0]-2, point[1]+2),
				color, penWidth );
}

////////////////////////////////////////////////////////////////////

QueryContext::QueryContext()
{	
	_stepIdx = 0;
}

////////////////////////////////////////////////////////////////////

QueryContext::~QueryContext()
{		
	
}

////////////////////////////////////////////////////////////////////

bool QueryContext::init(toolbox::DataPtr iData, 
						toolbox::StorageCellPtr iCell)
{	
	MDW_LOG_CONTEXT("Context initialization");
	
	_storageCell = iCell;

	{
		MDW_LOG_CONTEXT("File data decoding ");
	
		MDW_LOG_DEBUG("Data size:" << iData->size() );
	
		// Load the source image
		PointMatrix decoded = cv::imdecode(cv::Mat(*iData.get()), 1 );
		if (NULL == decoded.data)
		{
			MDW_LOG_ERROR("Unable to decode data: Interrupting.");
			return false;
		}
		
		/*
		int imgRes = decoded.rows * decoded.cols;
		const int maxRes = 800*600;
		// resize if needed
		if (imgRes > maxRes)
		{
			float surface_ratio = (float) maxRes / (float) imgRes;
			double ratio = sqrt( surface_ratio );
			int cols =  (int) (ratio * decoded.cols);
			int rows =  (int) (ratio * decoded.rows);

			MDW_LOG_INFO("Reducing resolution to " << cols << "-" << rows << " ratio = " << ratio);			
			cv::resize(decoded, _srcImg, cv::Size(cols, rows), 0, 0, cv::INTER_AREA );
		}
		else*/
		{
			_srcImg = decoded;
		}

		// Compute parameters for this image
		_parameters.init(_srcImg);	 
	
		MDW_LOG_DEBUG("Context init completed OK.");
	}
	
	return true;	
}

////////////////////////////////////////////////////////////////////

void QueryContext::log(const PointMatrix& iImg)
{
	_stepIdx++;
	
	// Create a filename for the img logfile
	std::stringstream filenameStream;
	
	filenameStream 	<< "Debug_" << _stepIdx << toolbox::ScopedContext::currentContext() << ".jpg";
	std::string imgLogFileName = filenameStream.str();
	
	// Convert back to jpeg dumpable format
	const char* ext = ".jpg";
	std::vector<int> compression_params;
	std::vector<unsigned char> outData;
	cv::imencode( ext, iImg, outData, compression_params);
    
    // copy to storable...
	toolbox::DataPtr data(new toolbox::Data());
	std::copy(  outData.begin(), 
				outData.end(), 
				std::back_inserter(* data.get()));
	
	// Write to cell storage.
	toolbox::DataGroup debugGroup("steplogs");
	_storageCell->dataSet(imgLogFileName, data);
	
	MDW_LOG_INFO("Logged debug image [" << imgLogFileName << "]");	
}

////////////////////////////////////////////////////////////////////

void QueryContext::log(const ConnectedSet& iGraph)
{
	PointMatrix copy = getSourceImage().clone();
	draw(iGraph, copy);
	log(copy);
}

////////////////////////////////////////////////////////////////////

void QueryContext::log(const std::set<Node*>& iSets)
{	
	PointMatrix copy = getSourceImage().clone();
	std::set<Node*>::const_iterator it;
	for(it  = iSets.begin();
		it != iSets.end();
		++it)
	{
		drawPoint(copy, (*it)->center(), Color::Red, 2);	
	}
	log(copy);
}

////////////////////////////////////////////////////////////////////

void QueryContext::log(const std::list<ConnectedSet>& iSets)
{	
	PointMatrix copy = getSourceImage().clone();
	std::list<ConnectedSet>::const_iterator it;
	for(it  = iSets.begin();
		it != iSets.end();
		++it)
	{
		draw(*it, copy);
	}
	log(copy);
}

////////////////////////////////////////////////////////////////////

void QueryContext::log(const ConnectedSetStats& iStats)
{
	PointMatrix copy = getSourceImage().clone();
	draw(iStats, copy);
	log(copy);
}

////////////////////////////////////////////////////////////////////

void QueryContext::log(const ConnectedSet& iGraph, const ConnectedSetStats& iStats)
{
	PointMatrix copy = getSourceImage().clone();
	draw(iGraph, copy);
	draw(iStats, copy);
	log(copy);
}

////////////////////////////////////////////////////////////////////

void QueryContext::draw(const ConnectedSet& iGraph, PointMatrix& copy)
{	
	ConnectedSet::const_iterator zoneIt;
	for (zoneIt  = iGraph.begin();
		 zoneIt != iGraph.end();
		 ++zoneIt) 
	{
		Node* zone = zoneIt->first;
		drawPoint(copy, zone->center(), Color::Green, _parameters._penWidth );
							
		std::set< Node* >::iterator segIt;
		for (segIt  = zoneIt->second.begin();
			 segIt != zoneIt->second.end();
			 ++segIt)  
		{
			Node* otherNode = *segIt;
			cv::line(copy, zone->center_i(), otherNode->center_i(), Color::Blue, _parameters._penWidth );							
		}			
	}  
}

////////////////////////////////////////////////////////////////////

void QueryContext::draw(const ConnectedSetStats& iGraph, PointMatrix& copy)
{	
	// Draw enclosing rect and center in green
	drawPoint(copy, iGraph.getEnclosingRectCenter(), Color::Green, _parameters._penWidth );
	
	PointF other3 = iGraph.getEnclosingRectMin();
	other3[1] = iGraph.getEnclosingRectMax()[1];
	PointF other4 = iGraph.getEnclosingRectMax();
	other4[1] = iGraph.getEnclosingRectMin()[1];
		
	cv::line(copy, cv::Point(iGraph.getEnclosingRectMin()), cv::Point(other3), Color::Green,	_parameters._penWidth );	
	cv::line(copy, cv::Point(iGraph.getEnclosingRectMin()), cv::Point(other4), Color::Green,	_parameters._penWidth );	
	cv::line(copy, cv::Point(iGraph.getEnclosingRectMax()), cv::Point(other3), Color::Green,	_parameters._penWidth );	
	cv::line(copy, cv::Point(iGraph.getEnclosingRectMax()), cv::Point(other4), Color::Green,	_parameters._penWidth );	
		
	// Draw gravity center in red
	drawPoint(copy, iGraph.getGravityCenter(), Color::Red, _parameters._penWidth );
}
	
////////////////////////////////////////////////////////////////////
