#pragma once
#include "Shape.hpp"
#include "ShapeHandler.hpp"

#include <iostream>
#include "Geometry.hpp"
#include <list>

//////////////////////////////////////////////////////////////////////

class ShapeText : public Shape
{
	public:
	
		ShapeText(const ConnectedSet& set, const PointI& corner, int width, int height);
		
		virtual const std::string getName() const { return std::string("TEXT"); }
		
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;
									
	private:		
		PointI _corner;
		int _width;
		int _height;							
};

//////////////////////////////////////////////////////////////////

class ShapeTextHandler : public ShapeHandler
{
	public:
		
		virtual const std::string getName() const { return std::string("TEXT"); }
	
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const ;
		
};
