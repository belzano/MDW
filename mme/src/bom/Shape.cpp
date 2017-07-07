#include "Shape.hpp"
#include "ConnectedSet.hpp"
#include "ConnectedSetStats.hpp"
#include "Node.hpp"

//////////////////////////////////////////////////////////////////////

bool Shape::couldAbsorb(const ConnectedSet& iOther) const
{
	const double absorbptionDistance = 5;

	ConnectedSet::const_iterator it;
	for(it  = iOther.begin();
		it != iOther.end();
		++it)
	{
		if (distance(it->first) > absorbptionDistance)
			return false;
	}
	
	return true;
}

//////////////////////////////////////////////////////////////////////

double Shape::distance(const Node* ) const
{
	return 10000;
}

