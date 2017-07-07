#include "ShapeCross.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"

#include <ostream>
#include <list>
#include <set>
#include <map>


//////////////////////////////////////////////////////////////////////

ShapeCross::ShapeCross(const ConnectedSet& iSet)
: Shape(iSet) 
{}

//////////////////////////////////////////////////////////////////////

void ShapeCross::serializeAsSvg(std::ostream& ioOut, 
								const Parameters& ) const
{
	ioOut 	<< "<cross TODO ";                  
	ioOut 	<< "/>";
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void ShapeCrossHandler::findAndMark( const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const

{
	// one node-4 and four node-1: 
	// Cross
	if (iStats.getProfile().size() != 2)
		return;
		
	if (iStats.getProfile().find(1) == iStats.getProfile().end())
		return;
	
	if (iStats.getProfile().find(4) == iStats.getProfile().end())
		return;
			
	ioFoundShapesMarked.insert(std::make_pair(1, build(iGraph, iParams)));
}
	
//////////////////////////////////////////////////////////////////

std::shared_ptr<Shape> ShapeCrossHandler::build(const ConnectedSet& set,  
												const Parameters& ) const
{
	// TODO
	return std::shared_ptr<Shape>(new ShapeCross(set));	
}

