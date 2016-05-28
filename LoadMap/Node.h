/*
 * Node.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include "limits.h"
#include <vector>
using namespace std;

enum Direction { LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN };
#define DIRECTIONS_NUM 8

class Node {
private:
	vector<Node *> neighbors;
	bool occupied;

public:
	int row;
	int col;
	double fValue;
	double gValue;
	double hValue;
	Node *cameFrom;

	Node();
	void setNode(int row, int col, bool occupied);
	void setOccupied();
	virtual ~Node();

	bool operator<(const Node& node) const
	{
		return (row*INT_MAX + col < node.row*INT_MAX + node.col);
	}
};

#endif /* NODE_H_ */
