/*
 * Robot.h
 *
 *  Created on: May 28, 2016
 *      Author: Eylam Milner & Lucas Aids
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot
{
 	PlayerClient* playerClinet;
 	Position2dProxy* posProxy;
 	LaserProxy* laserProxy;
// 	ConfigurationManager* configMgr;

	public:
 		//Robot constructor
		Robot(char* IP, int PortNum ,int gridRows);

		// Robot distructor
		virtual ~Robot();

		// Robot position
		double Xpos;
		double Ypos;
		double Yaw;
		int gridRows;

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
		void setSpeed(float xSpeed, float angularSpeed);
		void Read();
};

#endif /* ROBOT_H_ */
