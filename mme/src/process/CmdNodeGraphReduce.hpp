#pragma once


#include <list>
#include <set>
#include <vector>

#include <iostream>
#include "Geometry.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "QueryContext.hpp"
#include "Parameters.hpp"
#include "NodeGeoIndex.hpp"
#include "Node.hpp"

using namespace std;

class ConnectedSet;

//////////////////////////////////////////////////////////////////////

class CmdNodeGraphReduce
{
	public: 

		static void execute(QueryContext& iContext,
					        ConnectedSet& oGraph);

	private:
 
 
		void process(QueryContext& iContext,
					        ConnectedSet& oGraph);
 
		CmdNodeGraphReduce(QueryContext& iContext, const Parameters& iParams);

		void graph_buildGraph(const vector<LineI>& iLines, ConnectedSet& oGraph);
						
		void geometry_mergeNeighbourNodes(ConnectedSet& ioGraph, int zoneRadius);
		
		bool geometry_hookNeighbourSegmentToNode(ConnectedSet& ioGraph, int zoneRadius);
		
		bool graph_concatConsecutiveSegments(ConnectedSet& iZones, float maxAngle, float absorbRadius);

		bool extrapolateLeaves(ConnectedSet& ioGraph, int mergeRadius);

		bool realign(ConnectedSet& ioGraph);
			
	    bool onDifferentSides(Node*, Segment* , Segment*);		
		bool flatAngle(Node*, Segment* , Segment*);
		bool minorAngle(Node*, Segment* , Segment*);
		
		
		QueryContext& _context;	
		const Parameters _parameters;
		NodeGeoIndex _geoIndex;
};


