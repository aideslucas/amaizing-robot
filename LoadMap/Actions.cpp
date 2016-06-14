/*
 * Actions.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "Actions.h"

Actions::Actions(Robot* mybot)
{
	_robot = mybot;
	_actionToDo = NULL;
	_numOfActions = 0;
}

Actions* Actions::SetAction()
{
	// Initialize index
	int index;

	// Going over all of the actions
	for(index = 0; index<_numOfActions; index++)
	{
		// If the action is available
		if(_actionToDo[index]->pathIsClear())
		{
			// Return value
			return _actionToDo[index];
		}
	}

	// Return value
	return NULL;
}

Actions* Actions::ActionAdd(Actions* action)
{
	// Create the action array
	Actions** currAction = new Actions*[_numOfActions + 1];

	// If no actions
	if (!currAction)
	{
		// Return value
		return NULL;
	}

	// Initialize index
	int i;

	// Going over all of the actions in the vector
	for (i = 0; i < _numOfActions; ++i)
	{
		// Insert action to the action array
		currAction[i] = _actionToDo[i];
	}

	// Set the action
	currAction[i] = action;

	// free the actions array
	delete [] _actionToDo;

	// Increase the number of actions
	_numOfActions++;

	// Set the action to be done
	_actionToDo = currAction;

	// Return value
	return (this);
}

Actions::~Actions()
{
	delete [] _actionToDo;
	delete _robot;
}

