#pragma once


#include <list>
#include <set>
#include <vector>

#include <iostream>
#include "Geometry.hpp"

#include "QueryContext.hpp"
#include "Parameters.hpp"
#include "Node.hpp"

using namespace std;

class ConnectedSet;

//////////////////////////////////////////////////////////////////////

class CmdNodeGraphExtract
{
	public: 

		static void execute(QueryContext& iContext,
						    PointMatrix& src, 
					        ConnectedSet& oGraph);

	private:
 
		void process( PointMatrix& src, ConnectedSet& oGraph);
 
		CmdNodeGraphExtract(QueryContext& iContext, const Parameters& iParams);

		void buildGraph(PointMatrix& src, ConnectedSet& oGraph);

		QueryContext& _context;	
		const Parameters _parameters;
};


