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
#include "Point.h"
using namespace std;

class Node {
public:
	bool occupied;
	double fValue;
	double gValue;
	double hValue;
	Point parrent;

	Node();
	Node(const Node& node);
	virtual ~Node();
};

#endif /* NODE_H_ */
