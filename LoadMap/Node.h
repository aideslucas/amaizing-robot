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

class Node {
public:
	int row;
	int col;

	Node();
	Node(int x, int y);
	virtual ~Node();

	bool operator<(const Node& node) const
	{
		return (row*INT_MAX + col < node.row*INT_MAX + node.col);
	}
};

#endif /* NODE_H_ */
