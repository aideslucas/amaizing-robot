/*
 * Map.h
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>

using namespace std;

class Map {
private:
	unsigned int width;
	unsigned int height;
	vector<vector<bool> > map;
	vector<vector<bool> > inflotedMap;
	vector<unsigned char> pixels;
	vector<unsigned char> inflotedPixels;
	double mapResolution;
	double robotHeight;
	double robotWidth;

	bool checkIfCellIsOccupied(int i, int j);
	void setInflotedCellIsOccupied(int i, int j);
	void printMap() const;
	void printInflotedMap() const;

public:
	Map(double mapResolution, double robotHeight, double robotWidth);
	void loadMap(const string mapFile);
	void saveMap(const string mapFile);
	void inflateObstacles();
	virtual ~Map();
};

#endif /* MAP_H_ */
