/*
 * Node.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

enum Direction { LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN };
#define DIRECTIONS_NUM 8

class Node {
private:
	int row;
	int col;
	vector<Node *> neighbors;
	bool occupied;
	double fValue;
	double gValue;
	double hValue;
	Node *cameFrom;

public:
	Node();
	void setNode(int row, int col, bool occupied);
	void setOccupied();
	virtual ~Node();
};

#endif /* NODE_H_ */
