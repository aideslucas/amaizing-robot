/*
 * PathPlanner.h
 *
 *  Created on: Jun 12, 2016
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "ConfigurationManager.h"
#include "Path.h"
#include "WaypointManager.h"
#include "FindWayPoint.h"
#include "Move.h"

class PathPlanner : public Path
{
	public:

		PathPlanner(Robot* robot, WaypointManager* wayPointMgr);
		virtual ~PathPlanner();
		Actions* getPathStart();
};

#endif /* PATHPLANNER_H_ */
