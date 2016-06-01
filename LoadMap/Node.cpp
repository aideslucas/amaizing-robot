/*
 * Node.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Node.h"

Node::Node() {
	this->row = 0;
	this->col = 0;
	this->occupied = 0;
	this->fValue = INT_MAX;
	this->hValue = INT_MAX;
	this->gValue = INT_MAX;
}

Node::Node(int x, int y)
{
	this->row = y;
	this->col = x;
	this->occupied = 0;
	this->fValue = INT_MAX;
	this->hValue = INT_MAX;
	this->gValue = INT_MAX;
}

Node::Node(const Node& node)
{
	this->col = node.col;
	this->row = node.row;
	this->occupied = node.occupied;
	this->fValue = node.fValue;
	this->hValue = node.hValue;
	this->gValue = node.gValue;
	this->parentRow = node.parentRow;
	this->parentCol = node.parentCol;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

