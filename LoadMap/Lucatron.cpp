/*
 * Lucatron.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: colman
 */

#include "Lucatron.h"

using namespace std;

Lucatron::Lucatron(char* IP, int PortNum, ConfigurationManager* Config, int gridRows, ParticleFilter* pf, WaypointManager* wpMgr, Map* map)
{
	// Initialize robot's data members
	_playerClinet = new PlayerClient(IP, PortNum);
	_posProxy 	  = new Position2dProxy(_playerClinet);
	_laserProxy   = new LaserProxy(_playerClinet);
	_configMgr    = Config;
	_gridRows	  = gridRows;
	_pf 		  = pf;
	_wpMgr 		  = wpMgr;
	_map 		  = map;

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
	// Gets the position of the robot before read
	Point location;
	location.x = getXpos();
	location.y = getYpos();
	double Yaw = getYaw();

	// Read
	_playerClinet->Read();

	// Gets the position of the robot after read
	double currX   = getXpos();
	double currY   = getYpos();
	double currYaw = getYaw();

	// Get how much the robot moved
	Point delta;
	delta.x = currX - location.x;
	delta.y = currY - location.y;
	double deltaTeta = currYaw	 - Yaw;

	// Update particles
	_pf->update(location, Yaw, delta, deltaTeta, getLaser());

	_pf->paint(_map);
	_map->saveMap("CurrParticleGuess.png");
	_pf->unpaint(_map);

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

void Lucatron::setYaw(double Yaw) {
	double currYaw = getYaw();
	double diff = Yaw - currYaw;
	double turnSpeed = 0.2;

	if (diff < 0 || diff > 180)
	{
		turnSpeed = -0.2;
	}

	setSpeed(0,turnSpeed);

	while (abs(getYaw() - Yaw) > YAW_DIFFERNCE)
	{
		Read();
	}

	setSpeed(0,0);
}

void Lucatron::goToWaypoint()
{
	while (!_wpMgr->isInWaypoint(getXpos(), getYpos()))
	{
		setSpeed(0.2,0);
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

