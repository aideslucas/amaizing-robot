/*
 * Graph.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Map.h"
#include "set"
#include "Point.h"

typedef struct node
{
	bool occupied;
	double fValue;
	double gValue;
	double hValue;
	Point parrent;
}
Node;

class Graph {
private:
	double	graphResolutionInCM;
	double	resolutionRelation;
public:
	vector<vector<Node> > nodes;
	void buildGraphFromMap(const Map map);
	Graph(double graphResolutionInCM);
	virtual ~Graph();
	Point getPointFromCordinates(Cordinates cordinate);
	Cordinates getCordinatesFromPoint(Point point);
	void paintPathOnMap(Map *map, vector<Point> path, int r, int g, int b);
	void paintPathOnMap(Map *map, Point point, int r, int g, int b);
};

#endif /* GRAPH_H_ */
