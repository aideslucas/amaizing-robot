/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: colman
 */

#include "PathPlanner.h"

PathPlanner::PathPlanner(Robot* robot, WaypointManager* wayPointMgr) : Path(robot)
{

	// Set the actions to be made
	_actions 	= new Actions*[ACTION_COUNT];
	_actions[0] = new FindWayPoint(robot, wayPointMgr);
	_actions[1] = new Move(robot, wayPointMgr);

	// Add the action to the actions vector
	_actions[0]->ActionAdd(_actions[1]);
	_actions[1]->ActionAdd(_actions[0]);

	// Set the start of the path
	_pathStart = _actions[0];
}

Actions* PathPlanner::getPathStart()
{
	return _pathStart;
}

PathPlanner::~PathPlanner()
{
	for(int i = 0; i < ACTION_COUNT; i++)
	{
		delete _actions[i];
	}
}

