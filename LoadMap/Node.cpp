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
}

Node::Node(int x, int y)
{
	this->row = y;
	this->col = x;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

