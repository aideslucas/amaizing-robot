/*
 * WalkPath.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#include "WalkPath.h"

WalkPath::WalkPath(Robot* myRobot, ConfigurationManager* configMgr, WaypointManager* wayPointMgr, ParticleFilter* pf)
{
	_pf = pf;
	//	_curr = pln->getStartPoint();
	_Robot = myRobot;
	_wayPointsMgr = wayPointMgr;
	_configMgr = configMgr;
}

void WalkPath::Walk()
{
	Waypoint wayPoint;

	set<Waypoint>::iterator currWay;

	_Robot->Read();

	double Xlocation = _Robot->getXpos();
	double Ylocation = _Robot->getYpos();
	double Yaw		 = _Robot->getYaw();

	for (currWay = (_wayPointsMgr->waypoints).begin(); currWay != (_wayPointsMgr->waypoints).end(); ++currWay)
	{
		wayPoint = *currWay;
		_Robot->Read();


		_wayPointsMgr->setNextWaypoint(wayPoint);

//		_curr->startCond();

		while (true)
		{
//			if(_curr->stopCond())
//			{
				// Perform the next behavior according to the plan
//			    _curr = _curr->selectNextBehavior();

//			    _robot->Read();

			    // if we hit the way point break, and go on to the next way point
				if (_wayPointsMgr->isInWaypoint(_Robot->getXpos(), _Robot->getYpos()))
				{
					break;
				}

//				if (!_curr)
//					break;
//			}

			// Do the current behavior's action
//			_curr->action();

			_Robot->setSpeed(0.5,0.1);

			_Robot->Read();

			// Gets the position of the robot after read
			double currX   = _Robot->getXpos();
			double currY   = _Robot->getYpos();
			double currYaw = _Robot->getYaw();

			double deltaX = currX - Xlocation;
			double deltaY = currY - Ylocation;
			double deltaTeta = currYaw	 - Yaw;

			// Update particles
			Point point;
			point.x = Xlocation;
			point.y = Ylocation;
			Point deltaPoint;
			deltaPoint.x = deltaX;
			deltaPoint.y = deltaY;
			_pf->update(point, Yaw, deltaPoint, deltaTeta, _Robot->getLaser());

			Xlocation = currX;
			Ylocation = currY;
			Yaw = currYaw;
		}
	}
}

WalkPath::~WalkPath()
{
	// TODO Auto-generated destructor stub
}

