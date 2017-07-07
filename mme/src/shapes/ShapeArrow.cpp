#include "ShapeArrow.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"

#include <ostream>
#include <list>
#include <set>
#include <map>


//////////////////////////////////////////////////////////////////////

ShapeArrow::ShapeArrow(	const ConnectedSet& set, 
						PointI head, 	PointI tail, 
						PointI wing1,	PointI wing2	) : 
			Shape(set), 
			_head(head), _tail(tail), 
			_wing1(wing1), _wing2(wing2)
{}

//////////////////////////////////////////////////////////////////////

void ShapeArrow::serializeAsSvg(std::ostream& ioOut, 
								const Parameters& ) const
{
	ioOut 	<< "<line "
			<< " stroke=\"blue\" stroke-width=\"5\" "
			<< "x1=\"" << _head[0] << "\" "
			<< "y1=\"" << _head[1] << "\" "
			<< "x2=\"" << _tail[0] << "\" "
			<< "y2=\"" << _tail[1] << "\" ";                  
	ioOut 	<< "/>";
	ioOut 	<< "<line "
			<< " stroke=\"blue\" stroke-width=\"5\" "
			<< "x1=\"" << _head[0] << "\" "
			<< "y1=\"" << _head[1] << "\" "
			<< "x2=\"" << _wing1[0] << "\" "
			<< "y2=\"" << _wing1[1] << "\" ";                  
	ioOut 	<< "/>";
	ioOut 	<< "<line "
			<< " stroke=\"blue\" stroke-width=\"5\" "
			<< "x1=\"" << _head[0] << "\" "
			<< "y1=\"" << _head[1] << "\" "
			<< "x2=\"" << _wing2[0] << "\" "
			<< "y2=\"" << _wing2[1] << "\" ";                  
	ioOut 	<< "/>";
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void ShapeArrowHandler::findAndMark( const ConnectedSet& iGraph, const ConnectedSetStats& iStats,
								  std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
								  const Parameters& iParams) const
{	
	// An arrow has 3 leaf nodes	
	if (iStats.getProfile().find(1) == iStats.getProfile().end())
		return;
	
	if (iStats.getProfile().find(1)->second != 3)
		return;
		
	// Get the leaves
	std::set<Node*> leaves;	
	ConnectedSet::const_iterator it;
	for(it  = iGraph.begin();
		it != iGraph.end();
		++it)		
	{
		if (it->second.size() == 1)
			leaves.insert(it->first);
	}
			
	// Loop on nodes and find the possible head
	for(it  = iGraph.begin();
		it != iGraph.end();
		++it)		
	{
		Node* head = it->first;
		if (it->second.size() <= 2)
			continue;
		findAndMark_PointingTo(iGraph, head, leaves, ioFoundShapesMarked, iParams);
	}	
}

//////////////////////////////////////////////////////////////////

void ShapeArrowHandler::findAndMark_PointingTo(const ConnectedSet& iSet, 
											Node* head,
											std::set<Node*>& leaves, 
											std::multimap<float, std::shared_ptr<Shape> >& ioFoundShapesMarked,
											const Parameters& ) const
{	
	

	std::multimap<float, Node*> distFromHead;
	std::set<Node*>::iterator it;
	for(it  = leaves.begin();
		it != leaves.end();
		++it)		
	{
		distFromHead.insert(std::make_pair((*it)->distance(head) , *it) );
	}
	
	std::multimap<float, Node*>::iterator theIt = distFromHead.begin();
	std::multimap<float, Node*>::iterator wing1 = theIt; ++theIt;
	std::multimap<float, Node*>::iterator wing2 = theIt; ++theIt;
	std::multimap<float, Node*>::iterator tail  = theIt;
	
	float mark = 1.0;

	// Tail should be as long as possible
	mark *= abs(tail->first - wing2->first)/tail->first;
	mark *= abs(tail->first - wing1->first)/tail->first;
	
	// wings at same distance from tail -> head
	float dist1 = Segment(tail->second, head).distanceToLine(wing1->second);
	float dist2 = Segment(tail->second, head).distanceToLine(wing2->second);
	mark *= 1.0 / std::max<float>(1.0, abs(dist2 - dist1));

	// TODO check angles
	
	std::shared_ptr<Shape> theArrow(new ShapeArrow( iSet,
													head->center_i(), 
													tail->second->center_i(), 
													wing1->second->center_i(), 
													wing2->second->center_i()));		
	ioFoundShapesMarked.insert(std::make_pair(mark, theArrow));
}
	
//////////////////////////////////////////////////////////////////


