/*
 * WalkPath.h
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#ifndef WALKPATH_H_
#define WALKPATH_H_

#include "Robot.h"
#include "WaypointManager.h"
#include "Waypoint.h"
#include "ParticleFilter.h"
class WalkPath
{
//	Behavior* _curr;
//	LocalizationManager* _localization_manager;
	Robot* _Robot;
	ConfigurationManager* _configMgr;
	WaypointManager* _wayPointsMgr;
	ParticleFilter* _pf;
	public:
		WalkPath(Robot* myRobot, ConfigurationManager* configMgr, WaypointManager* wayPointsMgr, ParticleFilter* pf);
		virtual ~WalkPath();
		void Walk();
};

#endif /* WALKPATH_H_ */
