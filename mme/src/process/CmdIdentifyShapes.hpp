#pragma once


#include <list>
#include <vector>
#include <set>

#include <iostream>
#include <memory>


#include "Geometry.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Parameters.hpp"
#include "QueryContext.hpp"

#include "Shape.hpp"
#include "ShapeHandler.hpp"
#include "ConnectedSet.hpp"

#include "ShapeHandlerRegistry.hpp"

//////////////////////////////////////////////////////////////////////

class CmdIdentifyShapes
{
	public: 
 
		CmdIdentifyShapes(QueryContext& iContext,
						  const Parameters& iParams) : _context(iContext), _parameters(iParams) {}
		
		bool search( const ConnectedSet& iSet,
					 const ShapeHandlerSet& handlers,			 
					 std::list< std::shared_ptr<Shape> >& ioFoundShapes) ;
		
	private:

		QueryContext& _context;
		const Parameters _parameters;		
};


