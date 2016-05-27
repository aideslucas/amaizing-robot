/*
 * Node.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Node.h"

Node::Node() {
	neighbors.resize(DIRECTIONS_NUM);
	this->fValue = 0;
	this->gValue = 0;
	this->hValue = 0;
	this->cameFrom = 0;
}

void Node::setOccupied()
{
	this->occupied = true;
}

void Node::setNode(int row, int col, bool occupied)
{
	this->row = row;
	this->col = col;
	this->occupied = occupied;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

