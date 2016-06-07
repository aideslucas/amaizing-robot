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

	// Create a robot instance
	Robot myRobot("localhost", 6665, &configMgr, 3);

	// Check Lucatron's movement
	while (true)
	{
		myRobot.setSpeed(0.5, 0.5);
		myRobot.Read();
	}

	// Return value
	return 0;
}
