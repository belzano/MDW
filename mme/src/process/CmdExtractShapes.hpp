#pragma once


#include <list>
#include <vector>

#include <iostream>
#include <memory>

#include <set>

#include "Geometry.hpp"
#include "Parameters.hpp"
#include "Shape.hpp"
#include "Node.hpp"
#include "ConnectedSet.hpp"

#include "CmdNodeGraphSplit.hpp"

#include "ShapeHandlerRegistry.hpp"

class QueryContext;

using namespace std;


//////////////////////////////////////////////////////////////////////

class CmdExtractShapes
{
	public: 
 		static void execute (QueryContext& iQuery, 
							ConnectedSet& iGraph, 
							list<std::shared_ptr<Shape> >& oShapes);

	private:
			
		CmdExtractShapes(QueryContext& iContext, const Parameters& iParams) : 
						_context(iContext), 
						_parameters(iParams),
						_cmdSplit(iContext, iParams)
						{}
		
		CmdExtractShapes();
		
		int process (ConnectedSet& iGraph, list<std::shared_ptr<Shape> >& oShapes);

		typedef enum
		{
			Disjoint,
			Closed,
			Identity,
			Lines
		} SubSetType;
	
		void GetSubSets(SubSetType type,
						const ConnectedSet& iSet,
						std::list<ConnectedSet>& ioSplittedSets);
				
		
		void extractShapes(  const std::list<ConnectedSet>& theSourceSetsList,
							 SubSetType type,
							 const ShapeHandlerSet& handlers,
							 std::list<ConnectedSet>& oResidualSetsToAnalyse,
							 std::list<std::shared_ptr<Shape> >& ioShapes,
							 float sizeRatio);
		
		void extractShapes(  const ConnectedSet& theSourceSet, 
							 SubSetType type,
							 const ShapeHandlerSet& handlers,
							 std::list<ConnectedSet>& oResidualSetsToAnalyse,
							 float sizeRatio,
							 std::list<std::shared_ptr<Shape> >& ioShapes);

		void filterBySize(std::list<ConnectedSet>& ioSets, double distFromGravRatio, std::list<ConnectedSet>& oRemoved);
		void groupSmallSets(const std::list<ConnectedSet>& iSets, std::list<ConnectedSet>& oNotUsed, std::list<ConnectedSet>& oCreated);

		
		void identifyShapes(const std::list<ConnectedSet >& iConnectedSets,
							const ShapeHandlerSet& handlers,
							std::list<std::shared_ptr<Shape> >& ioShapes,
							 std::list<ConnectedSet >& theIdentifiedSets);
		void getResidualSubsets (const ConnectedSet& iGraph,
							     const std::list<ConnectedSet >& iConnectedSets,
							     std::list<ConnectedSet >& ioOpenedSets);			
						
		bool couldBeAbsorbed(	const ConnectedSet& iConnectedSet,
								const std::list<std::shared_ptr<Shape> >& ioShapes);
		
		bool removeOverlap(	ConnectedSet& iSet,	const std::shared_ptr<Shape>& ioShape);		
									
		QueryContext& _context;
		const Parameters _parameters;
		CmdNodeGraphSplit _cmdSplit;
};


