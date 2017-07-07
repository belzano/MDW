#pragma once

#include <map>
#include <set>
#include <list>


#include "Geometry.hpp"
#include "opencv2/highgui/highgui.hpp"

class Node;

//////////////////////////////////////////////////////////////////

class ConnectedSet : public std::map<Node*, std::set<Node*> >
{
	public:
		void add(Node* node1);
	
		void link(Node* node1, Node* node2);	
		void unlink(Node* node1, Node* node2);	

		void unlink(const ConnectedSet& iOther);
		void merge(const ConnectedSet& iOther);	
};

//////////////////////////////////////////////////////////////////

typedef std::shared_ptr<ConnectedSet> ConnectedSetPtr;
