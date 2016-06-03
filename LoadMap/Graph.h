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
#include "set"
#include "Point.h"

class Graph {
private:
	double	graphResolutionInCM;
	double	resolutionRelation;
public:
	vector<vector<Node> > nodes;
	void buildGraphFromMap(const Map map);
	Graph(double graphResolutionInCM);
	virtual ~Graph();
	Point getPointFromCordinates(cordinates cordinate);
	cordinates getCordinatesFromPoint(Point point);
	void paintPathOnMap(Map *map, vector<Point> path, int r, int g, int b);
	void paintPathOnMap(Map *map, Point point, int r, int g, int b);
};

#endif /* GRAPH_H_ */
