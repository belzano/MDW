#pragma once

#include <memory>
#include <map>

#include "Shape.hpp"

class Parameters;
class ConnectedSet;
class ConnectedSetStats;

//////////////////////////////////////////////////////////////////////

class ShapeHandler
{
	public:
		ShapeHandler()	{}
	
		virtual const std::string getName() const = 0;
	
		virtual void findAndMark( const ConnectedSet& iSet, 
								  const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const = 0;

};
