/*
 * Main.cpp
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */

#include "Map.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main()
{
	// Parameters from parameters file
	string	mapFile;
	double 	robotStartX;
	double 	robotStartY;
	double 	robotStartYAW;
	double 	goalX;
	double 	goalY;
	double 	robotHeight;
	double 	robotWidth;
	double 	mapResolutionCM;
	double 	gridResolutionCM;

	// Open parameters file
	ifstream parameters;
	parameters.open("parameters.txt");

	if (parameters.is_open())
	{
		string line;
		string lineName;

		// Get Map File - line contains map: path
		getline(parameters,line);
		std::istringstream mapLine(line);
		mapLine >> lineName >> mapFile;

		// Get Robot starting position - line contains startLocation: x y yaw
		getline(parameters,line);
		istringstream startLocationLine(line);
		startLocationLine >> lineName >> robotStartX >> robotStartY >> robotStartYAW;

		// Get Goal - line contains goal: x y
		getline(parameters,line);
		istringstream goalLine(line);
		goalLine >> lineName >> goalX >> goalY;

		// Get Robot Size - line contains robotSize: height width
		getline(parameters,line);
		istringstream sizeLine(line);
		sizeLine >> lineName >> robotHeight >> robotWidth;

		// Get Map resolution in CM - line contains MapResolutionCM: resolution
		getline(parameters,line);
		istringstream mapResolutionLine(line);
		mapResolutionLine >> lineName >> mapResolutionCM;

		// Get Grid resolution in CM - line contains GridResolutionCM: resolution
		getline(parameters,line);
		istringstream gridResolutionLine(line);
		gridResolutionLine >> lineName >> gridResolutionCM;

		parameters.close();
	}
	else
	{
		cout << "Unable to open file";
		return 0;
	}

	// Creating a map object with the given parameters
	Map map(mapResolutionCM, robotHeight, robotWidth);

	// Loading map
	map.loadMap(mapFile);

	// Inflate all of the obstacles in the give map
	map.inflateObstacles();

	// Save the new inflated map the a new file
	map.saveMap("infloatedMap.png");

	// Return value
	return 0;
}
