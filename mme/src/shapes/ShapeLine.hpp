#pragma once
#include "Shape.hpp"
#include "Segment.hpp"
#include "ShapeHandler.hpp"

#include <iostream>
#include "Geometry.hpp"
#include <list>

//////////////////////////////////////////////////////////////////////

class ShapeLine : public Shape
{
	public:
	
		ShapeLine(const ConnectedSet& set, Node* node1, Node* node2);

		virtual const std::string getName() const { return std::string("LINE"); }

		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;
		
		virtual double distance(const Node* iPoint) const;
				
	private:
		Segment _segment;
};

//////////////////////////////////////////////////////////////////

class ShapeLineHandler : public ShapeHandler
{
	public:		

		virtual const std::string getName() const { return std::string("LINE"); }
		
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const ;
		
};
