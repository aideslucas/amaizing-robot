/*
 * AStarAlgorithm.h
 *
 *  Created on: May 27, 2016
 *      Author: colman
 */

#ifndef ASTARALGORITHM_H_
#define ASTARALGORITHM_H_

#include "set"
#include "vector"
#include "Node.h"
#include "Graph.h"
#include "math.h"

class AStarAlgorithm {

private:
	vector<vector<Node> > graph;
	Point start;
	Point goal;
	set<Point> openSet;
	set<Point> closedSet;
	vector<Point> totalPath;

public:
	AStarAlgorithm(vector<vector<Node> > graph, Point start, Point goal);
	virtual ~AStarAlgorithm();
	vector<Point> StartAlgorithm();
	double getGValue(Point from, Point to);
	bool setContains(set<Point> nodeSet, Point current);
	Point getLowestFValue();
	double estimatedHeuristicCost(Point from, Point to);
	void reconstructPath();
	void fillHeuristic();
	void fillGAndFValues(Point from);
};

#endif /* ASTARALGORITHM_H_ */
