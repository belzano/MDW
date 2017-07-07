#pragma once
#include "Shape.hpp"
#include "ShapeHandler.hpp"


#include <iostream>
#include "Geometry.hpp"
#include <list>
#include <set>

class Node;

//////////////////////////////////////////////////////////////////////

class ShapeArrow : public Shape
{
	public:
	
		ShapeArrow(	const ConnectedSet& set,
					PointI head, 	PointI tail, 
					PointI wing1,	PointI wing2	);
					
		virtual const std::string getName() const { return std::string("ARROW"); }
	
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;
		
		PointI _head;
		PointI _tail;
		PointI _wing1;
		PointI _wing2;
};

//////////////////////////////////////////////////////////////////

class ShapeArrowHandler : public ShapeHandler
{
	public:
	
		virtual const std::string getName() const { return std::string("ARROW"); }
	
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const;

	private:
	
		void findAndMark_PointingTo( const ConnectedSet& iSet, 
									Node* head,
									std::set<Node*>& leaves, 
									std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
									const Parameters& iParams) const;
};
