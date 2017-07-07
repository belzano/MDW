#pragma once
#include "Shape.hpp"
#include "ShapeHandler.hpp"
#include "Geometry.hpp"

class Node;

//////////////////////////////////////////////////////////////////////

class ShapeCircle : public Shape
{
	public:
	
		ShapeCircle(const ConnectedSet&, const PointI& center, int radius);
		
		virtual const std::string getName() const { return std::string("CIRCLE"); }
	
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const;

		virtual double distance(const Node* iNode) const;

	private:
		PointI _center;
		int _radius;

};

//////////////////////////////////////////////////////////////////

class ShapeCircleHandler : public ShapeHandler
{
	public:	
	
		virtual const std::string getName() const { return std::string("CIRCLE"); }
		
		virtual void findAndMark( const ConnectedSet& iSet, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const;

		
		virtual std::shared_ptr<Shape> build(const ConnectedSet& iSet, const ConnectedSetStats& iStats, 
											const Parameters& iParams) const;
};
