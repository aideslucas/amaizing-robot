/*
 * Path.h
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#ifndef PATH_H_
#define PATH_H_

#include "Robot.h"
#include "Actions.h"

class Path
{
	public:

		// Path constructor & destructor
		Path(Robot* mybot);
		virtual ~Path();

		// Path start function
		virtual Actions* getPathStart();

		// Path data members
		Actions*  _pathStart;
		Actions** _actions;
		Robot* 	  _robot;
};

#endif /* PATH_H_ */
