#include "ConnectedSet.hpp"

#include "Node.hpp"

using namespace std;

/////////////////////////////////////////////////////////////////

void ConnectedSet::add(Node* node)
{
	if (find(node) != end())
		return;
		
	insert( { node, std::set<Node*>() } );
}

//////////////////////////////////////////////////////////////////

void ConnectedSet::link(Node* node1, Node* node2)
{
	if (node1 == node2)
		return;
	
	this->operator[](node1).insert(node2);
	this->operator[](node2).insert(node1);
}

//////////////////////////////////////////////////////////////////

void ConnectedSet::unlink(Node* node1, Node* node2)
{
	if (node1 == node2)
		return;
		
	ConnectedSet::iterator nodeIt;
	
	nodeIt = find(node1);
	if (nodeIt != end())
	{
		nodeIt->second.erase(node2);
		if (nodeIt->second.empty())
			erase(nodeIt);
	}
	
	nodeIt = find(node2);
	if (nodeIt != end())
	{
		nodeIt->second.erase(node1);
		if (nodeIt->second.empty())
			erase(nodeIt);
	}

}

//////////////////////////////////////////////////////////////////

void ConnectedSet::unlink(const ConnectedSet& iOther)
{
	// Remove all links included in other set
	ConnectedSet::const_iterator aSetIt;
	for(aSetIt  = iOther.begin();
		aSetIt != iOther.end();
		++aSetIt)
	{
		Node* node1 = aSetIt->first;
		
		// detach
		std::set<Node*>::iterator aNodeIt;
		for(aNodeIt  = aSetIt->second.begin();
			aNodeIt != aSetIt->second.end();
			++aNodeIt)
		{	
			Node* node2 = *aNodeIt;
			this->unlink(node1, node2);
		}

	}	
}

//////////////////////////////////////////////////////////////////

void ConnectedSet::merge(const ConnectedSet& iOther)
{
	// add all links included in other set
	ConnectedSet::const_iterator aSetIt;
	for(aSetIt  = iOther.begin();
		aSetIt != iOther.end();
		++aSetIt)
	{
		Node* node1 = aSetIt->first;
		this->add(node1);

		std::set<Node*>::iterator aNodeIt;
		for(aNodeIt  = aSetIt->second.begin();
			aNodeIt != aSetIt->second.end();
			++aNodeIt)
		{	
			Node* node2 = *aNodeIt;
			this->link(node1, node2);
		}

	}	
}
