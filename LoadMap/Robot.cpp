/*
 * Robot.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Robot.h"

using namespace std;

Robot::Robot(char* IP, int PortNum, ConfigurationManager* Config, int gridRows)
{
//    cout << "pp X: " << _posProxy->GetXPos() << " Y: " << _posProxy->GetYPos() << endl;

	//this->_playerClinet = &pc;
	//this->_posProxy 	= &pp;
	//this->_laserProxy 	= &lp;
	//this->_sonarProxy 	= &sp;

	this->_playerClinet = new PlayerClient(IP, PortNum);
	this->_posProxy 	= new Position2dProxy(_playerClinet);
	this->_laserProxy   = new LaserProxy(_playerClinet);
	this->_configMgr    = Config;
	this->_gridRows	    = gridRows;

	// Start motor
	this->_posProxy -> SetMotorEnable(true);

	// Player Client Read
	this->Read();

	cout << "Before odometry: " << endl;
	cout << "X: " << _posProxy->GetXPos() << " Y: " << _posProxy->GetYPos() << " Yaw: " << _posProxy->GetYaw() << endl;

	// Setting the location data
	_posProxy->SetOdometry(((double)Config->robotStartX / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/ (_configMgr->gridResolutionCM)),
						   ((_gridRows / _configMgr->gridResolutionCM) - (((double)Config->robotStartY) / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/
					  	    (_configMgr->gridResolutionCM))) ,Config->robotStartYAW*M_PI/180);

	// Out put the location data
	cout << " x " << getXpos() << " y " << getYpos() << "yaw" << getYaw() << endl;

	// Setting the location data
	_posProxy->SetOdometry(((double)Config->robotStartX / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/ (_configMgr->gridResolutionCM)),
						   ((_gridRows / _configMgr->gridResolutionCM) - (((double)Config->robotStartY) / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/
							(_configMgr->gridResolutionCM))),Config->robotStartYAW*M_PI/180);

	// Out put the location data
	cout << " x " << getXpos() << " y " << getYpos() << "yaw" << getYaw() << endl;

	cout << "After odometry: " << endl;
	cout << "X: " << _posProxy->GetXPos() << " Y: " << _posProxy->GetYPos() << " Yaw: " << _posProxy->GetYaw() << endl;
}

// Read the robot data
void Robot::Read()
{
	_playerClinet->Read();
}

// Set the moving speed
void Robot::setSpeed(float xSpeed, float angularSpeed)
{
	_posProxy->SetSpeed(xSpeed, angularSpeed);
}

// Check if the right path is clear
bool Robot::rightIsClear()
{
	// If the obstacle distance is grater than the minimum allowed
	if ((*this->_laserProxy)[LASER_RIGHT_VALUE] > MINIUM_ALLOWED_DISTANCE)
	{
		// Return true
		return (true);
	}

	// If there is an obstacle close by
	else
	{
		// Return false
		return false;
	}
}

bool Robot::leftIsClear()
{
	// If the obstacle distance is grater than the minimum allowed
	if ((*this->_laserProxy)[LASER_LEFT_VALUE] > MINIUM_ALLOWED_DISTANCE)
	{
		// Return true
		return (true);
	}

	// If there is an obstacle close by
	else
	{
		// Return false
		return false;
	}
}

bool Robot::straightIsClear()
{
	// If the obstacle distance is grater than the minimum allowed
	if ((*this->_laserProxy)[LASER_STRAIGHT_VALUE] > MINIUM_ALLOWED_DISTANCE)
	{
		// Return true
		return (true);
	}

	// If there is an obstacle close by
	else
	{
		// Return false
		return false;
	}
}

double Robot::getXpos()
{
	return ((this->_posProxy->GetXPos()) * this->_configMgr->gridResolutionCM);
}

double Robot::getYpos()
{
	return (((this->_gridRows / this->_configMgr->gridResolutionCM) - this->_posProxy->GetYPos()) * this->_configMgr->gridResolutionCM);
}

double Robot::getYaw()
{
	double yaw = 180*(this->_posProxy->GetYaw())/M_PI;

	if(yaw >= 0)
 	{
		return (yaw);
	}

	else
	{
		return (360+yaw);
	}
}

LaserProxy* Robot::getLaser()
{
	return (_laserProxy);
}

bool Robot::checkRange(int nStart, int nEnd)
{
	bool is_Good = true;

	for (int i = nStart; (i <= nEnd) && (is_Good); i++)
 	{
 		is_Good = (this->_laserProxy->GetRange(i) > MINIUM_ALLOWED_DISTANCE);
 	}

 	return (is_Good);
}

double Robot::getLaserSpec()
{
	return(((this->_laserProxy->GetMaxAngle() * 180 / M_PI) + 120 ) / 0.36);
}

void Robot::drive(int movingDist)
{
	double radYaw = this->_posProxy->GetYaw();
	double locationX = this->_posProxy->GetXPos();
	double locationY = this->_posProxy->GetYPos();


	locationX += (cos(radYaw) * movingDist);
	locationY += (sin(radYaw) * movingDist);

	double currX = getXpos();
	double currY = getYpos();

	while(currX < locationX)
	{
		this->_playerClinet->Read();
		this->_posProxy->SetSpeed(0.2, 0.0);
		currX = getXpos();
		currY = getYpos();
		cout << currX << endl;
	}

	this->_posProxy->SetSpeed(0.0,0.0);
}

/*

void Robot::move(ConfigurationManager currConfig)
{
    float speed = 0.5;
    float angle = 0.0;

    // Obstacle position
    double Xobs = 0.0;
    double Yobs = 0.0;

    // Sensor angle, relative to robot
    int radAngleVec[5] = {dtor(90), dtor(25), dtor(0), dtor(-25), dtor(-90)};

    // Keep the robot going
    while (true)
    {
        // Initializing speed
        speed = 1.0;

        // Initializing angle
        angle = 0.0;

        // Read data
        _playerClinet->Read();

        // Output robot's current X,Y locations and angle
        cout << "X: "     << _posProxy->GetXPos()
             << ", Y: "   << _posProxy->GetYPos()
             << ", Yaw: " << _posProxy->GetYaw() << endl;

        // Output robot's sonar data
        cout << _sonarProxy << endl;

        int val = int(_sonarProxy)[0]);

        // Checking for obstacles in path
        // If there is an obstacle on the RIGHT (90 deg)
        if (val < 0.8)
        {
        	_sonarProxy[9];
            // Adjust speed
            speed -= 0.1;

            // Adjust angle
            angle += 0.6 * ( 1 - _sonarProxy[0]);

            // Set obstacle position
            Xobs = _posProxy->GetXPos() + (_sonarProxy[0] * cos(_posProxy->GetYaw() + radAngleVec[0]));
            Yobs = _posProxy->GetYPos() + (_sonarProxy[0] * cos(_posProxy->GetYaw() + radAngleVec[0]));


            // Notify about the current obstacle
            cout << "There is an obstacle to my right (90), "
                << _sonarProxy[0]     << " away."
                << " At X: " << Xobs
                << ", Y: "   << Yobs << endl;
        }

        // If there is an obstacle on the RIGHT (25 deg)
        if (_sonarProxy[1] < 0.8)
        {
            // Adjust speed
            speed -= 0.2;

            // Adjust angle
            angle += 0.8 * (1 - _sonarProxy[1]);

            // Set obstacle position
            Xobs = _posProxy->GetXPos() + (_sonarProxy[1] * cos(_posProxy->GetYaw() + radAngleVec[1]));
            Yobs = _posProxy->GetYPos() + (_sonarProxy[1] * cos(_posProxy->GetYaw() + radAngleVec[1]));


            // Notify about the current obstacle
            cout << "There is an obstacle to my right (25), "
                << _sonarProxy[1]     << " away."
                << " At X: " << Xobs
                << ", Y: "   << Yobs << endl;
        }

        // If there is an obstacle on the Front (0 deg)
        if (_sonarProxy[2] < 0.8)
        {
            // Adjust speed
            speed -= 0.3;

            // Find the clearest path
            // If right is more clear, adjust right
            if ((_sonarProxy[1] + _sonarProxy[0]) > (_sonarProxy[3] + _sonarProxy[4]))
            {
                // Adjust angle
                angle -= 1 - _sonarProxy[2];
            }

            // If left is more clear, adjust left
            else
            {
                // Adjust angle
                angle += 1 - _sonarProxy[2];
            }

            // Set obstacle position
            Xobs = _posProxy->GetXPos() + (_sonarProxy[2] * cos(_posProxy->GetYaw() + radAngleVec[2]));
            Yobs = _posProxy->GetYPos() + (_sonarProxy[2] * cos(_posProxy->GetYaw() + radAngleVec[2]));

            // Notify about the current obstacle
            cout << "There is an obstacle to my right (0), "
                << _sonarProxy[2]     << " away."
                << " At X: " << Xobs
                << ", Y: "   << Yobs << endl;
        }

        // If there is an obstacle on the LEFT (-25 deg)
        if (_sonarProxy[3] < 0.8)
        {
            // Adjust speed
            speed -= 0.2;

            // Adjust angle
            angle -= 0.8 * (1 - _sonarProxy[3]);

            // Set obstacle position
            Xobs = _posProxy->GetXPos() + (_sonarProxy[3] * cos(_posProxy->GetYaw() + radAngleVec[3]));
            Yobs = _posProxy->GetYPos() + (_sonarProxy[3] * cos(_posProxy->GetYaw() + radAngleVec[3]));


            // Notify about the current obstacle
            cout << "There is an obstacle to my right (-25), "
                << _sonarProxy[3]     << " away."
                << " At X: " << Xobs
                << ", Y: "   << Yobs << endl;
        }

        // If there is an obstacle on the LEFT (-90 deg)
        if (_sonarProxy[4] < 0.8)
        {
            // Adjust speed
            speed -= 0.1;

            // Adjust angle
            angle -= 0.6 * (1 - _sonarProxy[4]);

            // Set obstacle position
            Xobs = _posProxy->GetXPos() + (_sonarProxy[4] * cos(_posProxy->GetYaw() + radAngleVec[4]));
            Yobs = _posProxy->GetYPos() + (_sonarProxy[4] * cos(_posProxy->GetYaw() + radAngleVec[4]));

            // Notify about the current obstacle
            cout << "There is an obstacle to my right (-90), "
                << _sonarProxy[4]     << " away."
                << " At X: " << Xobs
                << ", Y: "   << Yobs << endl;
        }

        // Set the robot with the new speed and angle
        _posProxy->SetSpeed(speed, angle);
    }
}
*/

Robot::~Robot()
{
	delete _playerClinet;
	delete _posProxy;
	delete _laserProxy;
}
