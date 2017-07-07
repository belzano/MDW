#pragma once
#include "Shape.hpp"
#include "ShapeHandler.hpp"


#include <iostream>
#include "Geometry.hpp"
#include <list>

//////////////////////////////////////////////////////////////////////

class ShapeCross : public Shape
{
	public:
	
		ShapeCross(const ConnectedSet& iSet);
		
		virtual const std::string getName() const { return std::string("CROSS"); }
		
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;
};

//////////////////////////////////////////////////////////////////

class ShapeCrossHandler : public ShapeHandler
{
	public:
		
		virtual const std::string getName() const { return std::string("CROSS"); }
	
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const ;
		
		virtual std::shared_ptr<Shape> build(const ConnectedSet& iSet,  
											const Parameters& iParams) const;
};
