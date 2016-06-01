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
	bool occupied;
	int row;
	int col;
	double fValue;
	double gValue;
	double hValue;
	int parentRow;
	int parentCol;

	Node();
	Node(int x, int y);
	Node(const Node& node);
	virtual ~Node();

	void operator()(int col, int row)
	{
		this->col = col;
		this->row = row;
	}
	bool operator<(const Node& node) const
	{
		return (row*INT_MAX + col < node.row*INT_MAX + node.col);
	}
/*	void operator=(const Node& node)
	{
		this->col = node.col;
		this->row = node.row;
		this->occupied = node.occupied;
		this->fValue = node.fValue;
		this->hValue = node.hValue;
		this->gValue = node.gValue;
		this->parent = node.parent;
	}*/
	bool operator==(const Node& node) const
	{
		return (this->col == node.col && this->row == node.row);
	}
	bool operator!=(const Node& node) const
	{
		return (this->col != node.col || this->row != node.row);
	}
};

#endif /* NODE_H_ */
