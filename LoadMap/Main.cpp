/*
 * Main.cpp
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */

#include "Map.h"
#include "iostream"

using namespace std;

int main()
{
	// Robot size and map's resolution
	double  mapResolution;
	double  robotSize;
	char 	mapFileName[50];

	// Receive map file path
	cout << "Please enter a map file name (no relative path): " << endl;
	cin  >>	mapFileName;

	// Receive robot size
	cout << "Please insert the size of the robot: " << endl;
	cin  >> robotSize;

	// Receive map resolution
	cout << "Please insert the resolution of the current map: " << endl;
	cin  >> mapResolution;

	// Creating a map object with the given parameters
	Map map(mapResolution, robotSize);

	// Loading map
	map.loadMap(mapFileName);

	// Inflate all of the obstacles in the give map
	map.inflateObstacles();

	// Save the new inflated map the a new file
	map.saveMap("infloatedMap.png");

	// Return value
	return 0;
}
