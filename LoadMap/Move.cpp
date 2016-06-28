/*
 * Move.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "Move.h"

Move::Move(Robot* mybot, WaypointManager* wayPointMgr):Actions(mybot)
{
	_wayPointMgr = wayPointMgr;
}

Move::~Move() {}

bool Move::pathIsClear()
{
	// Initializing variables
	double laserSpec;
	bool InRange;

	// Set the variables value
	laserSpec = _robot->getLaserSpec();
	InRange	  = _robot->checkRange(laserSpec / 2 - LASER, laserSpec / 2 + LASER);

	// Return value
	return (InRange);
}

bool Move::pathNotClear()
{
	// Initializing variables
	bool IsinWayPoint;

	// Read robot date
	_robot->Read();

	//IsinWayPoint = _wayPointMgr->isInWaypoint(_robot->getXpos(), _robot->getYpos());
	return (!pathIsClear() || (IsinWayPoint));
}

void Move::Do()
{
	_robot->setSpeed(SPEED, 0.0);
}
