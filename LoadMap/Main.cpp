/*
 * Main.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"
#include "iostream"

using namespace std;

int main()
{
	//double mapResolution = 0.025;
	//double robotSize = 0.3;

	// Robot size and map's resolution
	double mapResolution;
	double robotSize;

	// Receive robot size
	cout << "Please insert the size of the robot: " << endl;
	cin  >> robotSize;

	// Receive map resolution
	cout << "Please insert the resolution of the current map: " << endl;
	cin  >> mapResolution;

	// Creating a map object with the given parameters
	Map map(mapResolution, robotSize);

	// Loading map
	map.loadMap("roboticLabMap.png");

	// Inflate all of the obstacles in the give map
	map.inflateObstacles();

	// Save the new inflated map the a new file
	map.saveMap("infloatedMap_3.png");

	// Return value
	return 0;
}
