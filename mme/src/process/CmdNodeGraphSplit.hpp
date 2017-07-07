#pragma once


#include <list>
#include <vector>

#include <iostream>
#include <memory>

#include <set>

#include "Geometry.hpp"
#include "Parameters.hpp"
#include "Node.hpp"
#include "ConnectedSet.hpp"

class QueryContext;

using namespace std;


//////////////////////////////////////////////////////////////////////

class CmdNodeGraphSplit
{
	typedef enum
	{
		Clockwise,
		Trigo,
		Any
	} Rotation;
	
	
	private:
		CmdNodeGraphSplit();
	
	public: 
 
		CmdNodeGraphSplit(QueryContext& iContext, const Parameters& iParams) : 
						_context(iContext), _parameters(iParams) {}

							
		void splitPaint(const ConnectedSet& iSet, list< ConnectedSet >& connectedSet);
		
		bool ClosedPathLookup(const ConnectedSet& iSrc,
							  std::list<ConnectedSet>& ioOutPaths);

		void splitAtAngles(const ConnectedSet& iSet, 
							std::list<ConnectedSet>& ioSplittedSets);
							
	private:	
	
		void recursivePaintNeighbours(const ConnectedSet& iSet, Node* iNode, std::map<Node*, int>& colors);
	
	

		void visitLeaves( const ConnectedSet& iSrc, Node* iLeaf, std::set<Node*>& ioLeaves);

		bool recursiveClosedPathLookup( const ConnectedSet& iSrc, Node* iFirst,
									   ConnectedSet& path, Node* iPrevious, Node* iCurrent,
								       std::list<ConnectedSet>& ioOutPaths,
								       std::set<Node*>& ioVisited, bool canFlagAsVisited,
								       Rotation iRotation);



		void ExtractSimplePath(const ConnectedSet& ioGraph, 
								 ConnectedSet& ioResult);
										 
		void visitUntilSingularity( const ConnectedSet& iSrc, 
									ConnectedSet::const_iterator iNodeIt,
									ConnectedSet& ioSet);

		QueryContext& _context;
		const Parameters _parameters;
		
};


