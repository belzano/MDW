#pragma once
#include "Shape.hpp"
#include "ShapeHandler.hpp"

//////////////////////////////////////////////////////////////////////

class ShapeEllipse : public Shape
{
	public:
		
		ShapeEllipse(const ConnectedSet& set, PointF center, int radius_x, int radius_y);
	
		virtual const std::string getName() const { return std::string("ELLIPSE"); }
	
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;

		PointF _center;
		int _radius_x;
		int _radius_y;

};

//////////////////////////////////////////////////////////////////

class ShapeEllipseHandler : public ShapeHandler
{
	public:
	
		virtual const std::string getName() const { return std::string("ELLIPSE"); }
		
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const;
};
