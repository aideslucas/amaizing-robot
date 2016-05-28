/*
 * Graph.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Map.h"

class Graph {
private:
	double	graphResolutionInCM;
	double	resolutionRelation;
public:
	vector<vector<Node *> > nodes;
	void buildGraphFromMap(const Map map);
	Graph(double graphResolutionInCM);
	virtual ~Graph();
	Node getNodeFromCordinates(int x, int y);
	void paintPathOnMap(Map map, set<Node> path);
};

#endif /* GRAPH_H_ */
