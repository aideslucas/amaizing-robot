/*
 * Path.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "Path.h"

Path::Path(Robot* mybot)
{
	// Initialize the robot data member
	_robot = mybot;
}
Actions* Path::getPathStart()
{
	// Return action object - path start position
	return _pathStart;
}



Path::~Path() {}

