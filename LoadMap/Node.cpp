/*
 * Node.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Node.h"

Node::Node() {
	this->occupied = false;
	this->fValue = INT_MAX;
	this->hValue = INT_MAX;
	this->gValue = INT_MAX;
	this->parrent(0,0);
}

Node::Node(const Node& node)
{
	this->occupied = node.occupied;
	this->fValue = node.fValue;
	this->hValue = node.hValue;
	this->gValue = node.gValue;
	this->parrent = node.parrent;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

