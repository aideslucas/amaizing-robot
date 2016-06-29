/*
 * Lucatron.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: colman
 */

#include "Lucatron.h"

using namespace std;

Lucatron::Lucatron(char* IP, int PortNum, ConfigurationManager* Config, int gridRows, WaypointManager* wpMgr, Map* map, LocalizationManager* localizationManager)
{
	// Initialize robot's data members
	_playerClinet = new PlayerClient(IP, PortNum);
	_posProxy 	  = new Position2dProxy(_playerClinet);
	_laserProxy   = new LaserProxy(_playerClinet);
	_configMgr    = Config;
	_gridRows	  = gridRows;
	_wpMgr 		  = wpMgr;
	_map 		  = map;
	_localizationManager = localizationManager;

	// Start motor
	_posProxy -> SetMotorEnable(true);

	// Setting the location data
	_posProxy->SetOdometry(((double)Config->robotStart.x / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/ (_configMgr->gridResolutionCM)),
						   ((_gridRows / _configMgr->gridResolutionCM) - (((double)Config->robotStart.y) / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/
					  	    (_configMgr->gridResolutionCM))) ,Config->robotStartYAW*M_PI/180);

	this->Read();
}

// Read the robot data
void Lucatron::Read()
{
	double lastX = _Xpos;
	double lastY = _Ypos;
	double lastYaw = _Yaw;

	// Read
	_playerClinet->Read();

	_Xpos = getXpos();
	_Ypos = getYpos();
	_Yaw = getYaw();

	double deltaRow = this->_Xpos - lastY;
	double deltaCol = this->_Ypos - lastX;
	double deltaYaw = this->_Yaw - lastYaw;

	Position delta(deltaRow, deltaCol, deltaYaw);
	//_localizationManager->updateParticles(&delta, getLaserScan());

	cout << "X: " << _Xpos << " Y: " << _Ypos << " Yaw: " << _Yaw << endl;
}

float* Lucatron::getLaserScan()
{
	float* scan = new float[_laserProxy->GetCount()];

	for (unsigned int i = 0; i < _laserProxy->GetCount(); i++)
	{
		scan[i] = (*_laserProxy)[i];
	}

	return scan;
}

// Set the moving speed
void Lucatron::setSpeed(float xSpeed, float angularSpeed)
{
	_posProxy->SetSpeed(xSpeed, angularSpeed);
}

double Lucatron::getXpos()
{
	return ((_posProxy->GetXPos()) * _configMgr->gridResolutionCM);
	//return _localizationManager->getHighestBeliefParticle().getPosition().getCol();
}

double Lucatron::getYpos()
{
	return (((_gridRows / _configMgr->gridResolutionCM) - _posProxy->GetYPos()) * _configMgr->gridResolutionCM);
	//return _localizationManager->getHighestBeliefParticle().getPosition().getRow();
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
	//return _localizationManager->getHighestBeliefParticle().getPosition().getYaw();
}

void Lucatron::setYaw(double Yaw)
{
	double diff = _Yaw - Yaw;
	double turnSpeed = -0.12;

	if (diff < 0 || diff > 180)
	{
		turnSpeed = 0.12;
	}

	setSpeed(0,turnSpeed);

	while (abs(diff) > 2)
	{
		Read();
		diff = _Yaw - Yaw;
	}

	setSpeed(0,turnSpeed / 2);

	while (abs(diff) > 0.5)
	{
		Read();
		diff = _Yaw - Yaw;
	}

	setSpeed(0,turnSpeed / 4);

	while (abs(diff) > 0.3)
	{
		Read();
		diff = _Yaw - Yaw;
	}


	setSpeed(0,0);
}

void Lucatron::goToWaypoint()
{
	double speed = 0.12;

	setSpeed(speed,0);

	while (!_wpMgr->isNearWaypoint(getXpos(), getYpos(), getYaw()))
	{
		Read();
	}

	setSpeed(speed / 2, 0);

	while (!_wpMgr->isInWaypoint(getXpos(), getYpos(), getYaw()))
	{
		Read();
	}

	setSpeed(0,0);
}

Lucatron::~Lucatron()
{
	delete _playerClinet;
	delete _posProxy;
	delete _laserProxy;
}

