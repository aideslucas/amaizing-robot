/*
 * AStarAlgorithm.h
 *
 *  Created on: May 27, 2016
 *      Author: colman
 */

#ifndef ASTARALGORITHM_H_
#define ASTARALGORITHM_H_

#include <set>
#include <vector>
#include "Node.h"
#include "Graph.h"

class AStarAlgorithm {

private:
	vector<vector<Node> > graph;
	Node start;
	Node goal;

public:
	AStarAlgorithm(vector<vector<Node> > graph, Node start, Node goal);
	virtual ~AStarAlgorithm();
	set<Node> StartAlgorithm();
	double distance(Node from, Node to);
	bool setContains(set<Node> nodeSet, Node current);
	const Node getLowestFValue(const set<Node> nodeSet);

	int estimatedHeuristicCost(Node from, Node to);

	set<Node> reconstructPath(vector<Node> path, Node current);

};

#endif /* ASTARALGORITHM_H_ */
