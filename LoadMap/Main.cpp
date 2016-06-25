/*
 * Main.cpp
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */

#include "Map.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "AStarAlgorithm.h"
#include "ConfigurationManager.h"
#include "Robot.h"
#include "Cell.h"
#include "WaypointManager.h"
#include "WalkPath.h"
#include "ParticleFilter.h"
#include "Path.h"
#include "PathPlanner.h"

using namespace std;

int main()
{
	ConfigurationManager configMgr("parameters.txt");

	// Creating a map object with the given parameters
	Map map(configMgr.mapResolutionCM, configMgr.robotHeight, configMgr.robotWidth);

	// Loading map
	map.loadMap(configMgr.mapFile);

	// Inflate all of the obstacles in the give map
	map.inflateObstacles();

	// Create a graph from map to run the a star algorithm on it
	Graph graph(configMgr.gridResolutionCM);
	graph.buildGraphFromMap(map);

	Cell start = graph.getCellFromPoint(configMgr.robotStart);
	Cell goal = graph.getCellFromPoint(configMgr.goal);
	AStarAlgorithm algo(graph.nodes, start, goal);
	vector<Cell> path = algo.StartAlgorithm();
	graph.paintPathOnMap(&map, path,255,0,0);
	//graph.paintPathOnMap(&map, start,255,0,0);
	//graph.paintPathOnMap(&map, goal,0,0,255);
	// Save the new inflated map the a new file
	map.saveMap("infloatedMap.png");



	// Create a waypoint instance
	WaypointManager wpMgr(algo.StartAlgorithm(), configMgr.gridResolutionCM, configMgr.mapResolutionCM);

	//wpMgr.buildWaypointVector(3);

	for (int i = 0; i < wpMgr.waypoints.size(); i++)
	{
		printf("x = %d, y = %d, yaw = %d\n", wpMgr.waypoints[i].point.col, wpMgr.waypoints[i].point.row, wpMgr.waypoints[i].yaw);
	}

	ParticleFilter pf;
/*
	// Create a robot instance
	Robot myRobot("localhost", 6665, &configMgr, graph.nodes.size());

	// Create the path planner instance
	PathPlanner robotPath(&myRobot, &wpMgr);

	// Create the walk path instance
	WalkPath wpth(&myRobot, &configMgr, &wpMgr, &pf, &robotPath);

	// Start walking the path
	wpth.Walk();
*/

	Lucatron lucatron("localhost", 6665, &configMgr, graph.nodes.size());
	Waypoint wayPoint;
	lucatron.Read();

	double Xlocation = lucatron.getXpos();
	double Ylocation = lucatron.getYpos();
	double Yaw		 = lucatron.getYaw();

	for (int i = 0; i < wpMgr.waypoints.size(); i++)
	{
		wayPoint = wpMgr.waypoints[i];
		wpMgr.setNextWaypoint(wayPoint);

		lucatron.Read();

		while (!wpMgr.isInWaypoint(lucatron.getXpos(), lucatron.getYpos()))
		{
			lucatron.Read();
			lucatron.setSpeed(0.2,0);
		}

		lucatron.setSpeed(0,0);
		lucatron.setYaw(wayPoint.yaw);
	}

	// Return value
	return 0;
}
