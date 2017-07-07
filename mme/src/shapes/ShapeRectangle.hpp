#pragma once

#include "Shape.hpp"
#include "ShapeHandler.hpp"

#include <iostream>
#include "Geometry.hpp"
#include <list>

//////////////////////////////////////////////////////////////////////

class ShapeRectangle : public Shape
{
	public:
	
		ShapeRectangle(const ConnectedSet& iSet, const PointI& corner, int width, int height);
	
		virtual const std::string getName() const {return std::string("RECTANGLE");}
	
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;

		virtual double distance(const Node* iPoint) const;	
	
		PointI _corner;
		int _width;
		int _height;

};

//////////////////////////////////////////////////////////////////

class ShapeRectangleHandler : public ShapeHandler
{
	public:
		virtual const std::string getName() const {return std::string("RECTANGLE");}
		
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const;
			
	private:
		
		double computeMark(std::shared_ptr<ShapeRectangle> iShape, 
				           const ConnectedSet& iGraph, 
				           const Parameters& iParams) const;	
																	
};
//////////////////////////////////////////////////////////////////


