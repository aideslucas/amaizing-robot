/*
 * WaypointManager.h
 *
 *  Created on: Jun 4, 2016
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_
#include "Map.h"
#include <set>
#include "Graph.h"
#include "math.h"

using namespace std;
#include <iostream>

typedef struct waypoint
{
	Point point;
	double yaw;
}
Waypoint;

class WaypointManager {
public:
	set<Waypoint> waypoints;
	Waypoint currWaypoint;

	WaypointManager(vector<Cell> path, double gridResolution, double mapResolution);
	void buildWaypointVector(int numberOfCells);
	void setNextWaypoint(Waypoint Next);
	bool isInWaypoint(double x,double y);
	virtual ~WaypointManager();

private:
	vector<Cell> astarPath;
	bool isVerticle = 0;
	Waypoint nextWaypoint;
	double gridResolution;
	double mapResolution;

	double calculateYaw(double m, Cell from, Cell to);
	double calculateIncline(Cell from, Cell to);
};

#endif /* WAYPOINTMANAGER_H_ */
