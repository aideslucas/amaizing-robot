/*
 * Main.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"

int main() {
	double mapResolution = 1;
	double robotSize = 0.3;

	Map map(mapResolution, robotSize);
	map.loadMap("roboticLabMap.png");

	return 0;
}


