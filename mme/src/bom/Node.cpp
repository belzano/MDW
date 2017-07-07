#include "Node.hpp"

#include <iostream>

#include "Geometry.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;


////////////////////////////////////////////////////////////////////

Node* Node::createNewAsBarycentre(const std::set<Node*>& iNodes)
{	
	float x = 0, y = 0;
	int weight = 0;
	
	std::set<Node*>::const_iterator anIt;
	for (anIt  = iNodes.begin();
		 anIt != iNodes.end();
		 ++anIt)
	{
		int nodeWeight = 0;
		nodeWeight += (*anIt)->_weight;
		weight += nodeWeight;
		x += (*anIt)->_center[0] * nodeWeight;
		y += (*anIt)->_center[1] * nodeWeight;
	}
	
	PointF center(x/weight, y/weight);
	Node* newNode = new Node( center );
	newNode->_weight = weight; // set weight
	
	return newNode;
}

////////////////////////////////////////////////////////////////////

std::ostream& Node::toStream(std::ostream& ioStream)
{
	ioStream 	<< "[" 
				<< center_i()[0]<< ";" 
				<< center_i()[1] << "]";
	return ioStream;
}

std::ostream& operator<<(std::ostream& ioStream, Node& iNode)
{
	return iNode.toStream(ioStream);
}



