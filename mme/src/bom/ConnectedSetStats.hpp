#pragma once

#include <map>
#include <set>
#include <list>

#include "Geometry.hpp"

class ConnectedSet;
class Node;

typedef std::pair<Node*, Node*> Link;


//////////////////////////////////////////////////////////////////

class EnclosingRectangleStats
{
	public:	
		void compute(const ConnectedSet& set);
	
		PointF 	getEnclosingRectCenter() const;
		const PointF&  getEnclosingRectMin() const { return _enclosingRectMin; }
		const PointF&  getEnclosingRectMax() const { return _enclosingRectMax; }
		
	private:
		PointF  _enclosingRectMin;
		PointF  _enclosingRectMax;
		float 	_enclosingRectRefSize;		
};

//////////////////////////////////////////////////////////////////

class WalkedAngleStats
{
	public:	
		void compute(const ConnectedSet& set);
		bool isConnex() const;
		
		int getNumberOfEdges() const;

	private:
		std::list<float> _walkedAngles;
};

//////////////////////////////////////////////////////////////////

class ProfileStats
{
	public:	
		void compute(const ConnectedSet& set);
		
		const std::map<int, int>& getProfile() const;		
		bool isClosed() const;
		bool isCloseable() const;
		
	private:
		std::map<int, int> _graphProfile;
		int _nodeCount;
};

//////////////////////////////////////////////////////////////////

class GravityCenterStats
{
	public:	
		void compute(const ConnectedSet& set);
		const PointF& getGravityCenter() const;
		
		float getAverageDistanceFromGravityCenter() const { return _avgDistanceFromGravCenter; }
		const std::multimap<float, Node*>& getSortedDistanceFromGravCenter() const {return _sortedDistanceFromGravCenter; }
		
	private:
		void computeCenter(const ConnectedSet& set);
		void computeOthersMetrics(const ConnectedSet& set);
		
		PointF 	_gravityCenter;
		float _avgDistanceFromGravCenter;
		std::multimap<float, Node*> _sortedDistanceFromGravCenter;
};

//////////////////////////////////////////////////////////////////

class CentralAngleStats
{
	public:	
		void compute(const ConnectedSet& set, const PointF& center);

		// Check no backtracking when walking around gravity center; eg, central angle only increase or decrease
		bool isPerimeterBacktracking() const;
		
		void sliceAngles(const ConnectedSet& iSet, const PointF& center, 
						 std::list<std::pair<float, Node*> >& oAngles) const;
						 
	private:					 
		bool _isPerimeterBacktracking;
		
};

//////////////////////////////////////////////////////////////////

class ConnectedSetStats : 
		public EnclosingRectangleStats ,
		public ProfileStats,
		public GravityCenterStats,
		// Those 2 only apply under condition 
		public WalkedAngleStats, 
		public CentralAngleStats
{
	public:		
		void compute(const ConnectedSet& iSet);
};

//////////////////////////////////////////////////////////////////

