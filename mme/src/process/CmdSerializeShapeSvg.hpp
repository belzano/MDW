#pragma once


#include <list>
#include <vector>
#include <iostream>
#include <memory>

#include "Parameters.hpp"
#include "Shape.hpp"
#include "toolbox/Types.hpp"

class QueryContext;

//////////////////////////////////////////////////////////////////////

class CmdSerializeShapeSvg
{
	public: 
		static void execute(QueryContext& iQueryContext, 
							std::list<std::shared_ptr<Shape> >& iShapes,
							toolbox::DataPtr);
 
	private:
		CmdSerializeShapeSvg(const Parameters& iParams) : _parameters(iParams) {}
		
		void serialize( std::list<std::shared_ptr<Shape> >& iShapes,
						toolbox::DataPtr);
		
		const Parameters _parameters;
		
};


