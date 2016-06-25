/*
 * Lucatron.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: colman
 */

#include "Lucatron.h"

using namespace std;

Lucatron::Lucatron(char* IP, int PortNum, ConfigurationManager* Config, int gridRows)
{
	// Initialize robot's data members
	_playerClinet = new PlayerClient(IP, PortNum);
	_posProxy 	  = new Position2dProxy(_playerClinet);
	_laserProxy   = new LaserProxy(_playerClinet);
	_configMgr    = Config;
	_gridRows	  = gridRows;

	// Start motor
	_posProxy -> SetMotorEnable(true);

	// Player Client Read
	for (int i=0;i<20;i++)
	{
		this->Read();
	}

	// Setting the location data
	_posProxy->SetOdometry(((double)Config->robotStart.x / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/ (_configMgr->gridResolutionCM)),
						   ((_gridRows / _configMgr->gridResolutionCM) - (((double)Config->robotStart.y) / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/
					  	    (_configMgr->gridResolutionCM))) ,Config->robotStartYAW*M_PI/180);

	// Out put the location data
	cout << " x " << getXpos() << " y " << getYpos() << "yaw" << getYaw() << endl;

	// Setting the location data
	_posProxy->SetOdometry(((double)Config->robotStart.x / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/ (_configMgr->gridResolutionCM)),
						   ((_gridRows / _configMgr->gridResolutionCM) - (((double)Config->robotStart.y) / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/
							(_configMgr->gridResolutionCM))),Config->robotStartYAW*M_PI/180);

	// Out put the location data
	cout << " x " << getXpos() << " y " << getYpos() << "yaw" << getYaw() << endl;
}

// Read the robot data
void Lucatron::Read()
{
	_playerClinet->Read();
}

// Set the moving speed
void Lucatron::setSpeed(float xSpeed, float angularSpeed)
{
	_posProxy->SetSpeed(xSpeed, angularSpeed);
}

double Lucatron::getXpos()
{
	return ((_posProxy->GetXPos()) * _configMgr->gridResolutionCM);
}

double Lucatron::getYpos()
{
	return (((_gridRows / _configMgr->gridResolutionCM) - _posProxy->GetYPos()) * _configMgr->gridResolutionCM);
}

double Lucatron::getYaw()
{
	double yaw = 180*(_posProxy->GetYaw())/M_PI;

	if(yaw >= 0)
 	{
		return (yaw);
	}

	else
	{
		return (360+yaw);
	}
}

LaserProxy* Lucatron::getLaser()
{
	return (_laserProxy);
}

float Lucatron::getLeaserDist(int index)
{
	return (_laserProxy->GetRange(index));
}

bool Lucatron::checkRange(int nStart, int nEnd)
{
	bool is_Good = true;

	for (int i = nStart; (i <= nEnd) && (is_Good); i++)
 	{
 		is_Good = (this->getLeaserDist(i) > MINIUM_ALLOWED_DISTANCE);
 	}

 	return (is_Good);
}

double Lucatron::getLaserSpec()
{
	return(((_laserProxy->GetMaxAngle() * 180 / M_PI) + 120 ) / 0.36);
}

void Lucatron::drive(int movingDist)
{
	double radYaw    = _posProxy->GetYaw();
	double locationX = _posProxy->GetXPos();
	double locationY = _posProxy->GetYPos();


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

	_posProxy->SetSpeed(0.0,0.0);
}

void Lucatron::setYaw(double Yaw) {
	double currYaw = getYaw();
	double diff = Yaw - currYaw;
	double turnSpeed = 0.2;

	if (diff < 0 || diff > 180)
	{
		turnSpeed = -0.2;
	}

	setSpeed(0,turnSpeed);

	while (abs(diff) > 2)
	{
		Read();
		currYaw = getYaw();
		diff = Yaw - currYaw;
	}

	setSpeed(0,0);
}

Lucatron::~Lucatron()
{
	delete _playerClinet;
	delete _posProxy;
	delete _laserProxy;
}

