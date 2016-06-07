/*
 * Waypoint.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#include "Waypoint.h"

Waypoint::Waypoint() {
	// TODO Auto-generated constructor stub
	this->point.x = 0;
	this->point.y = 0;
	this->yaw = 0;
}

Waypoint::Waypoint(Point point, double yaw)
{
	this->point.x = point.x;
	this->point.y = point.y;
	this->yaw = yaw;
}

Waypoint::~Waypoint() {
	// TODO Auto-generated destructor stub
}

