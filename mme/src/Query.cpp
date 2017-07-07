
#include "mme/Query.hpp"

#include "toolbox/StringUtils.hpp"
#include "toolbox/ExecutionContext.hpp"
#include "toolbox/StorageCellLocalMemory.hpp"
#include "toolbox/Logger.hpp"
 

#include "Geometry.hpp"

#include "CmdPreprocess.hpp"
#include "CmdNodeGraphExtract.hpp"
#include "CmdExtractShapes.hpp"
#include "CmdSerializeShapeSvg.hpp"

#include "ConnectedSet.hpp"
#include "ApplicationConfig.hpp"
#include "Parameters.hpp"
#include "QueryContext.hpp"

#include <fstream>
#include <iterator>

namespace API
{
	
//////////////////////////////////////////////////////////////////////

Query::Query(toolbox::StorageCellPtr storage)
{
	_storage = storage;
}

///////////////////////////////////////////////////////////////////

void Query::toStorage() const
{
	MME_PTREEDOCUMENT_JSON_STORE("requestor", 		getRequestor(), 	_storage)
	MME_PTREEDOCUMENT_JSON_STORE("inputDetails",	getInputDetails(), 	_storage)
	MME_PTREEDOCUMENT_JSON_STORE("events", 			getEvents(), 		_storage)
	MME_PTREEDOCUMENT_JSON_STORE("state", 			getState(), 		_storage)	
}

///////////////////////////////////////////////////////////////////

void Query::fromStorage()
{
	MME_PTREEDOCUMENT_JSON_RETRIEVE("requestor", 		getRequestor(), 	_storage)
	MME_PTREEDOCUMENT_JSON_RETRIEVE("inputDetails",		getInputDetails(), 	_storage)
	MME_PTREEDOCUMENT_JSON_RETRIEVE("events", 			getEvents(), 		_storage)
	MME_PTREEDOCUMENT_JSON_RETRIEVE("state", 			getState(), 		_storage)		
}

///////////////////////////////////////////////////////////////////

int Query::process()
{
	QueryContext theQueryCtx;
	
	toolbox::DataPtr inputImage = getInput();
	if (! theQueryCtx.init(inputImage, _storage))
		return -1;
	
	// Loading data from storage
	fromStorage();
	
	// Preparing image 
	PointMatrix preprocessedImg;
	{
		MDW_LOG_CONTEXT("Preprocess");	
		CmdPreprocess::execute(theQueryCtx, preprocessedImg);
	}
	
	// Extract graph
	ConnectedSet theSet;
	{
		MDW_LOG_CONTEXT("ExtractGraph");
		CmdNodeGraphExtract::execute(theQueryCtx, preprocessedImg, theSet);
	}
		
	// Detect shapes on graph
	list< std::shared_ptr<Shape> > theShapes;
	{
		MDW_LOG_CONTEXT("ExtractShapes");
		CmdExtractShapes::execute(theQueryCtx, theSet, theShapes);	
	}

	// _storage->dataSet("shapes", serializedShapes);
	
	
	// Draw result
	{
		MDW_LOG_CONTEXT("StoreShapes");
		toolbox::Image::DataPtr theOutput(new toolbox::Data());
		CmdSerializeShapeSvg::execute(theQueryCtx, theShapes, theOutput);
		setOutput(theOutput);
	}
	
	getState().setStatus("Completed");
	getState().setProgression("100");

	// Saving object before exiting
	toStorage();
	
	return 0;
}
	
//////////////////////////////////////////////////////////////////////

#define INPUT_DATA_KEY toolbox::DataKey("input.jpg")
#define OUTPUT_DATA_KEY toolbox::DataKey("output.jpg")

const toolbox::Image::DataPtr Query::getInput() const
{
	return _storage->dataGet(INPUT_DATA_KEY);
}

//////////////////////////////////////////////////////////////////////

void Query::setInput(toolbox::Image::DataPtr iData)
{
	_storage->dataSet(INPUT_DATA_KEY, iData);
}
	
//////////////////////////////////////////////////////////////////////

void Query::setInput(const std::string& iFile)
{
	// Set Data
	std::ifstream file(iFile);	
	file >> std::noskipws;
	
	toolbox::DataPtr theData(new toolbox::Data());
	std::copy(  std::istream_iterator<char>(file), 
				std::istream_iterator<char>(), 
				std::back_inserter(*theData.get()));
	
	setInput(theData);
}

//////////////////////////////////////////////////////////////////////

const toolbox::Image::DataPtr Query::getOutput( toolbox::Image::SerializationFormat , 
												toolbox::Image::Resolution ) const
{
	// create key from params
	
	// lookup in storage
	
	// key exists: return value
	
	// else
	// create the data from the SVG
	// store the data generated
	
	// return data	
	
	return _storage->dataGet(OUTPUT_DATA_KEY);
}

//////////////////////////////////////////////////////////////////////

void Query::setOutput(toolbox::Image::DataPtr iData)
{
	_storage->dataSet(OUTPUT_DATA_KEY, iData);
}		
	
}
