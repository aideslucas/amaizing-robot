/*
 * Robot.h
 *
 *  Created on: May 28, 2016
 *      Author: Eylam Milner & Lucas Aids
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "ConfigurationManager.h"

using namespace PlayerCc;

class Robot
{
	PlayerClient* _playerClinet;
	Position2dProxy* _posProxy;
	LaserProxy* _laserProxy;
	SonarProxy* _sonarProxy;
	ConfigurationManager* _configMgr;

	public:

		//Robot constructor & destructor
		Robot(char* IP, int PortNum, ConfigurationManager* Config, int gridRows);
		virtual ~Robot();

		// Robot position
		double _Xpos;
		double _Ypos;
		double _Yaw;
		int    _gridRows;

		// Get the robot position
		double getXpos();
		double getYpos();
		double getYaw();

		// Set the robot position
		void setXpos(double Xpos);
		void setYpos(double Ypos);
		void setYaw(double  Yaw);

		// Check for obstacles
		bool straightIsClear();
		bool rightIsClear();
		bool leftIsClear();

		// Robot's Laser data
		float getLeaserDist(int index);
		bool checkRange(int nStart, int nEnd);
		double getLaserSpec();
		LaserProxy* getLaser();

		void drive(int configMgrToMove);
		void move(ConfigurationManager currConfig);
		void setSpeed(float xSpeed, float angularSpeed);
		void Read();
};

#endif /* ROBOT_H_ */
