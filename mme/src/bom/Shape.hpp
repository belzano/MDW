#pragma once

#include <ostream>
#include "Geometry.hpp"
#include "ConnectedSet.hpp"

class Parameters;
class Node;

//////////////////////////////////////////////////////////////////////

class Shape
{
	public:
		Shape(const ConnectedSet& iSet) : 
			_set(iSet) 
		{}
	
		virtual const std::string getName() const = 0;	
	
		virtual void serializeAsSvg(std::ostream& ioOut, 
									const Parameters& iParams) const = 0;
	
		virtual bool couldAbsorb(const ConnectedSet& iOther) const;
		virtual double distance(const Node* iPoint) const;
	
		const ConnectedSet& getSet() const { return _set; }
	
	public: 
		ConnectedSet _set;		
};
