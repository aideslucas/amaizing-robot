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

void Map::saveMap(const char* mapFile) {

	inflotedPixels.resize(width * height * 4);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			setInflotedCellIsOccupied(i, j);
		}
	}

	lodepng::encode(mapFile, inflotedPixels, width, height);
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
				for (int k = -1 * inflationRadius; k <= inflationRadius; k++)
				{
					for (int m = -1 * inflationRadius; m <= inflationRadius; m++)
					{
						if (i + k > 0 && i + k < height && j + m > 0 && j + m < width)
						{
							inflotedMap[i + k][j + m] = true;
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

void Map::setInflotedCellIsOccupied(int i, int j) {
	int c = (i * width + j) * 4;
	int color = (inflotedMap[i][j] ? 0 : 255);

	inflotedPixels[c] = color;
	inflotedPixels[c + 1] = color;
	inflotedPixels[c + 2] = color;
	inflotedPixels[c + 3] = 255;
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

