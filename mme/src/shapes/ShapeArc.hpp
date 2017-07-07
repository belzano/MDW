#pragma once
#include "Shape.hpp"
#include "ShapeHandler.hpp"


#include <iostream>
#include "Geometry.hpp"
#include <list>

//////////////////////////////////////////////////////////////////////

class ShapeArc : public Shape
{
	public:
	
		ShapeArc(const ConnectedSet& set);
		
		virtual const std::string getName() const { return std::string("Arc"); }
	
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;
		
};

//////////////////////////////////////////////////////////////////

class ShapeArcHandler : public ShapeHandler
{
	public:

		virtual const std::string getName() const { return std::string("Arc"); }
		
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const;

		virtual std::shared_ptr<Shape> build(const ConnectedSet& iSet,  
											const Parameters& iParams) const;
};
