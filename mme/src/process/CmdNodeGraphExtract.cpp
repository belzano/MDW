#include "CmdNodeGraphExtract.hpp"

#include "CmdNodeGraphReduce.hpp"

#include "ConnectedSet.hpp"

#include "toolbox/Logger.hpp"
#include "toolbox/StringUtils.hpp"

#include <iostream>
#include <set>

#include "Color.hpp"
#include "Geometry.hpp"

//#define CHRONO(x) toolbox::ScopedChrono aChrono(x);
#define CHRONO(x)

using namespace std;

////////////////////////////////////////////////////////////////////

void CmdNodeGraphExtract::execute(QueryContext& iContext,
								  PointMatrix& src, 
								  ConnectedSet& ioGraph)
{
	CmdNodeGraphExtract aCmd(iContext, iContext.getParameters());
	aCmd.process(src, ioGraph);			
}

////////////////////////////////////////////////////////////////////

CmdNodeGraphExtract::CmdNodeGraphExtract(QueryContext& iContext, 
										const Parameters& iParams) 
										: _context(iContext),
										  _parameters(iParams)
{			
}

////////////////////////////////////////////////////////////////////

void CmdNodeGraphExtract::process(PointMatrix& blackOnWhiteSkeleton, 
								  ConnectedSet& ioGraph)
{	
	buildGraph(blackOnWhiteSkeleton, ioGraph);
	
	CmdNodeGraphReduce::execute(_context, ioGraph);	
}

//////////////////////////////////////////////////////////////////////

int index(int rowIdx, int colIdx, int cols)
{
	return (rowIdx*cols + colIdx);
}

////////////////////////////////////////////////////////////////////

void checkAndConnect(ConnectedSet& oSet, unsigned char* data, Node** nodePtrArray, Node*& mainNode, int rowIdx, int colIdx, int colCount, int rowShift, int colShift)
{	
	int otherIndex = index(rowIdx+rowShift, colIdx+colShift, colCount);
	
	if (data[otherIndex] > Grayscale::Gray)
		return;	
	
	Node*& otherNode = nodePtrArray[otherIndex];
			
	if (mainNode == NULL)
		mainNode = new Node(colIdx, rowIdx);
	if (otherNode == NULL)
		otherNode = new Node(colIdx+colShift, rowIdx+rowShift);
	
	oSet.link(mainNode, otherNode);		
}

////////////////////////////////////////////////////////////////////

void CmdNodeGraphExtract::buildGraph(PointMatrix& blackOnWhiteSkeleton, 
							         ConnectedSet& oSet)
{
	CHRONO("buildGraph");
	
	// find neighbours and attach
	// o o x
	// o X x
	// o x x
	
	int rows = blackOnWhiteSkeleton.rows;
	int cols = blackOnWhiteSkeleton.cols;
	int border = 2; // on va pas se faire chier pour 2 px
	// Internally stored a BGR
	unsigned char* data = blackOnWhiteSkeleton.data;
	
	
	// NodePtr index, initialized with NULL
	Node** nodePtrArray = new Node*[rows * cols];
	memset( (void*) nodePtrArray, 0, rows*cols*sizeof(Node*));
	
    for (int rowIdx = border; rowIdx < rows - border; ++rowIdx)  
    {  		
		//MDW_LOG_DEBUG("Processing ROW " << rowIdx << "/" << rows - border << "("<< (rowIdx*100)/(rows - 2*border) <<"%)");
		
		for (int colIdx = border; colIdx < cols - border; ++colIdx)  
		{  			
			int mainIndex = index(rowIdx, colIdx, cols);
			if (data[mainIndex] > Grayscale::Gray)
				continue;
			
			//MDW_LOG_DEBUG("Found a non-white point: (" << (int) mainColor << ") at " << rowIdx << "," << colIdx);
			
			Node*& mainNode = nodePtrArray[mainIndex];
			
			checkAndConnect(oSet, data, nodePtrArray, mainNode, rowIdx, colIdx, cols,  1,  0); // Check South 
			checkAndConnect(oSet, data, nodePtrArray, mainNode, rowIdx, colIdx, cols,  1,  1); // Check South East
			checkAndConnect(oSet, data, nodePtrArray, mainNode, rowIdx, colIdx, cols,  0,  1); // Check East 
			checkAndConnect(oSet, data, nodePtrArray, mainNode, rowIdx, colIdx, cols, -1,  1); // Check North East			
		}
	}
	MDW_LOG_DEBUG("Graph built: " << oSet.size() << " nodes");
}
