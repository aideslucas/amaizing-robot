/*
 * Move.h
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#ifndef MOVE_H_
#define MOVE_H_

#include <iostream>
#include <math.h>
#include "ConfigurationManager.h"
#include "Actions.h"
#include "Robot.h"
#include "WaypointManager.h"

class Move : public Actions
{
	public:

		// Move constructor and destructor
		Move(Robot* mybot, WaypointManager* wayPointMgr);
		virtual ~Move();

		// Move Functions
		bool pathIsClear();
		bool pathNotClear();
		void Do();

		// Move Data Members
		WaypointManager* _wayPointMgr;
};

#endif /* MOVE_H_ */
