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
	this->fValue = 0;
	this->hValue = 0;
	this->gValue = 0;
	this->cameFromCol = 0;
	this->cameFromRow = 0;
}

Node::Node(int x, int y)
{
	this->row = y;
	this->col = x;
	this->occupied = 0;
	this->fValue = 0;
	this->hValue = 0;
	this->gValue = 0;
	this->cameFromCol = 0;
	this->cameFromRow = 0;
}

Node::Node(const Node& node)
{
	this->col = node.col;
	this->row = node.row;
	this->occupied = node.occupied;
	this->fValue = node.fValue;
	this->hValue = node.hValue;
	this->gValue = node.gValue;
	this->cameFromCol = node.cameFromCol;
	this->cameFromRow = node.cameFromRow;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

