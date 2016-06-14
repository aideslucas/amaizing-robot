/*
 * Actions.h
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#ifndef ACTIONS_H_
#define ACTIONS_H_

#include "Robot.h"

class Actions
{
	public:

		// Actions constructor and destructor
		Actions(Robot* mybot);
		virtual ~Actions();

		// Action Data Members
		Robot* 	  _robot;
		Actions** _actionToDo;
		int 	  _numOfActions;

		Actions* ActionAdd(Actions* action);
		Actions* SetAction();

		// Pure Virtual functions
		virtual bool pathIsClear() = 0;
		virtual bool pathNotClear() = 0;
		virtual void Do() = 0;

};

#endif /* ACTIONS_H_ */
