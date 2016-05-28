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
	vector<vector<point> > graph;
	Node start;
	Node goal;
	set<Node> openSet;
	set<Node> closedSet;
	vector<Node> totalPath;
public:
	AStarAlgorithm(vector<vector<point> > graph, Node start, Node goal);
	virtual ~AStarAlgorithm();
	vector<Node> StartAlgorithm();
	double distance(Node from, Node to);
	bool setContains(set<Node> nodeSet, Node current);
	Node getLowestFValue();
	double estimatedHeuristicCost(Node from, Node to);
	void reconstructPath();
	void fillHeuristic();
	void fillGAndFValues(Node from);
};

#endif /* ASTARALGORITHM_H_ */
