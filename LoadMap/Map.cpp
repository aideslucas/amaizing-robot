/*
 * Map.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include <iostream>

Map::Map(double mapResolution, double robotSize) {
	this->robotSize = robotSize;
	this->mapResolution = mapResolution;
}

void Map::loadMap(const char* mapFile) {

	lodepng::decode(pixels, width, height, mapFile);

	map.resize(height);
	for (int i = 0; i < height; i++) {
		map[i].resize(width);
	}


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}

	printMap();
}

void Map::inflateObstacles() {
	int robotSizeInPixels = robotSize / mapResolution;
	int inflationRadius = 0.5 * robotSizeInPixels;

	inflotedMap.resize(height);
		for (int i = 0; i < height; i++) {
			inflotedMap[i].resize(width);
		}
	// TODO: inflate obstacles
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j])
			{
				for (int ii = -inflationRadius; ii <= inflationRadius; ii++) {
					for (int jj = -inflationRadius; jj <= inflationRadius; jj++) {
						if (i + ii > 0 && i + ii < height && j + jj > 0 && j + jj < width)
						{
							inflotedMap[i + ii][j + jj] = true;
						}
					}
				}
			}
		}
	}

	printInflotedMap();
}

bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * width + j) * 4;
	int r = pixels[c];
	int g = pixels[c + 1];
	int b = pixels[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printMap() const {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << (map[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

void Map::printInflotedMap() const {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << (inflotedMap[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

