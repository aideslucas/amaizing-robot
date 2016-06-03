/*
 * Robot.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Robot.h"

using namespace std;

double DummyDouble;

Robot::Robot(char* IP, int PortNum, ConfigurationManager* Config, int gridRows)
{
	// Initialize Robot
	this->_playerClinet = new PlayerClient(IP, PortNum);
	this->_posProxy 	= new Position2dProxy(_playerClinet);
	this->_laserProxy   = new LaserProxy(_playerClinet);
	this->_configMgr    = Config;
	this->_gridRows	    = gridRows;

	// Start motor
	this->_posProxy -> SetMotorEnable(true);

	// Player Client Read
	this->Read();


	_posProxy->SetOdometry(((double)Config->start_x / (_configMgr->grid_resolution / _configMgr->map_resolution)/ (_configMgr->grid_resolution)), ((_gridRows / _configMgr->grid_resolution) - (((double)Config->start_y) / (_configMgr->grid_resolution / _configMgr->map_resolution)/ (_configMgr->grid_resolution))) ,Config->yaw*M_PI/180);
	cout << " x " << getXpos() << " y " << getYpos() << "yaw" << getYaw() << endl;


	_posProxy->SetOdometry(((double)Config->start_x / (_configMgr->grid_resolution / _configMgr->map_resolution)/ (_configMgr->grid_resolution)), ((_gridRows / _configMgr->grid_resolution) - (((double)Config->start_y) / (_configMgr->grid_resolution / _configMgr->map_resolution)/ (_configMgr->grid_resolution))) ,Config->yaw*M_PI/180);
	cout << " x " << getXpos() << " y " << getYpos() << "yaw" << getYaw() << endl;
}

void Robot::Read()
{

}

void Robot::setSpeed(float xSpeed, float angularSpeed)
{

}

bool Robot::rightIsClear()
{
	return false;
}

bool Robot::leftIsClear()
{

	return false;
}

bool Robot::straightIsClear()
{
	return false;
}

double Robot::getXpos()
{
	return (DummyDouble);
}

double Robot::getYpos()
{
	return (DummyDouble);
}

double Robot::getYaw()
{
	return (DummyDouble);
}

LaserProxy* Robot::getLaser()
{
	return (_laserProxy);
}

float Robot::getLeaserDist(int index)
{
	return (DummyDouble);
}

bool Robot::checkRange(int nStart, int nEnd)
{
	return (false);
}


double Robot::getLaserSpec()
{
	return(false);
}

void Robot::drive(int ConfigToMove)
{

}

Robot::~Robot()
{
	delete _playerClinet;
	delete _posProxy;
	delete _laserProxy;
}
