/*
 * FindWayPoint.h
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#ifndef FINDWAYPOINT_H_
#define FINDWAYPOINT_H_

#include "Actions.h"
#include "WaypointManager.h"
#include "ConfigurationManager.h"
#include "math.h"

class FindWayPoint: public Actions
{
	public:

		// FindWayPoint Constructor & destructor
		FindWayPoint(Robot* mybot, WaypointManager* wayPointMgr);
		virtual ~FindWayPoint();

		// FindWayPoint Functions
		bool pathIsClear();
		bool pathNotClear();
		void Do();

	private:

		// Data members
		bool 			 _isRight;
		double 			 _diffrence;
		WaypointManager* _wayPointMgr;
};

#endif /* FINDWAYPOINT_H_ */
