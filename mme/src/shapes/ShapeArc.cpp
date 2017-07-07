#include "ShapeArc.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"

#include <ostream>
#include <list>
#include <set>
#include <map>


//////////////////////////////////////////////////////////////////////

ShapeArc::ShapeArc(const ConnectedSet& set)
:Shape(set) 
{}

//////////////////////////////////////////////////////////////////////

void ShapeArc::serializeAsSvg(std::ostream& , 
								const Parameters& ) const
{
	return;
	//ioOut 	<< "<ARC TODO ";
	//ioOut 	<< "/>";
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void ShapeArcHandler::findAndMark(const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const
{
	// only node-2 and node-1: 
	// Opened basic figure (Arc)
	if (iStats.getProfile().size() != 2)
		return;
		
	if (iStats.getProfile().find(1) == iStats.getProfile().end())
		return;
		
	if (iStats.getProfile().find(2) != iStats.getProfile().end())
		return;

	ioFoundShapesMarked.insert(std::make_pair(1, build(iGraph, iParams)));
}
	
//////////////////////////////////////////////////////////////////

std::shared_ptr<Shape> ShapeArcHandler::build(const ConnectedSet& set,  
												const Parameters& ) const
{
	return std::shared_ptr<Shape>(new ShapeArc(set));	
}

