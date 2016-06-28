/*
 * FindWayPoint.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "FindWayPoint.h"

// FindWayPoint Constructor
FindWayPoint::FindWayPoint(Robot* robot, WaypointManager* wpm):Actions(robot)
{
	_wayPointMgr = wpm;
//	_isRight 	 = NULL;
//	_diffrence   = NULL;
}

bool FindWayPoint::pathIsClear()
{
	double yaw = _robot->getYaw();
	_diffrence = _wayPointMgr->currWaypoint.yaw - yaw;

	if(_diffrence == 0)
	{
		return false;
	}
	else if(_diffrence >= 180)
	{
		_isRight = 1;
		_diffrence = 360 - _diffrence;
	}
	else if (_diffrence < -180)
	{
		_isRight = 0;
		_diffrence = 360 + _diffrence;
	}
	else if (_diffrence > 0)
	{
		_isRight = 0;
	}
	else
	{
		_isRight = 1;
		_diffrence = abs(_diffrence);
	}
	if(_isRight)
	{
		return (_robot->checkRange(0, _diffrence * DEGREE_INDEXE));
	}
	else
	{
		return(_robot->checkRange( _robot->getLaserSpec() - (_diffrence * DEGREE_INDEXE),_robot->getLaserSpec() ));
	}
}

bool FindWayPoint::pathNotClear()
{
	if(_isRight)
	{
		return (!(_robot->checkRange(0, _diffrence * DEGREE_INDEXE)) || (abs(_robot->getYaw() - _wayPointMgr->currWaypoint.yaw) <= YAW_DIFFERNCE));
	}
	else
	{
		return(!(_robot->checkRange( _robot->getLaserSpec() - (_diffrence * DEGREE_INDEXE),_robot->getLaserSpec())) || (abs(_robot->getYaw() - _wayPointMgr->currWaypoint.yaw) <= YAW_DIFFERNCE)) ;
	}
}

void FindWayPoint::Do()
{
	if(_isRight)
	{
		_robot->setSpeed(0.0, RIGHT_SPEED);
	}
	else
	{
		_robot->setSpeed(0.0, LEFT_SPEED);
	}
}

// FindWayPoint Destructor
FindWayPoint::~FindWayPoint(){}
