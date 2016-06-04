/*
 * WaypointManager.cpp
 *
 *  Created on: Jun 4, 2016
 *      Author: colman
 */

#include "WaypointManager.h"

WaypointManager::WaypointManager(vector<Cell> path, double gridResolution, double mapResolution)
{
	this->astarPath = path;
	this->gridResolution = gridResolution;
	this->mapResolution = mapResolution;
}

// Creating way point every "num_of_cells" item on the path
void WaypointManager::buildWaypointVector(int numberOfCells)
{
	set<Waypoint>::iterator index = waypoints.begin();
	int counter = 0;
	double m;
	Waypoint current;

	for (int i = 0; i < astarPath.size(); i++)
	{
		if(i == 0)
		{
			m = calculateIncline(astarPath[i],astarPath[i+1]);
			current.point.x = astarPath[i].col;
			current.point.y = astarPath[i].row;
			current.yaw = calculateYaw(m, astarPath[i], astarPath[i+1]);
			waypoints.insert(index,current);
			++index;

			currWaypoint.point = current.point;
			currWaypoint.yaw = current.yaw;

			nextWaypoint.point = current.point;
			nextWaypoint.yaw = current.yaw;

		}
		else if (i == (astarPath.size() - 1))
		{
			current.point.x = astarPath[i].col;
			current.point.y = astarPath[i].row;
			current.yaw = calculateYaw(m, astarPath[i-1], astarPath[i]);
			waypoints.insert(index,current);
			++index;
		}
		else if (counter == numberOfCells)
		{
			m = calculateIncline(astarPath[i], astarPath[i+1]);

			current.point.x = astarPath[i].col;
			current.point.y = astarPath[i].row;
			current.yaw = calculateYaw(m, astarPath[i], astarPath[i+1]);
			waypoints.insert(index,current);
			++index;
			counter = 0;
		}
		else
		{
			double newM;
			bool isOldVarticle;
			isOldVarticle = isVerticle;
			newM = calculateIncline(astarPath[i], astarPath[i+1]);
			if((newM != m)||(isOldVarticle != isVerticle))
			{
				current.point.x = astarPath[i].col;
				current.point.y = astarPath[i].row;
				current.yaw = calculateYaw(newM, astarPath[i], astarPath[i+1]);
				waypoints.insert(index,current);
				++index;
				counter = 0;
			}
			m = newM;
		}

		counter++;
	}
}

double WaypointManager::calculateYaw(double m, Cell from, Cell to)
{
	double angle;

	if(!isVerticle)
	{
		angle = 180 * atan(m) / M_PI;
	}

	if (isVerticle)
	{
		if (to.row > from.row)
		{
			return (270);
		}
		else
		{
			return (90);
		}
	}
	else if (m == 0)
	{
		if (to.col > from.col)
		{
			return (angle);
		}
		else
		{
			return (180 + angle);
		}
	}
	else if (m > 0)
	{
		if (to.row > from.row)
		{
			return (360 - angle);
		}
		else
		{
			return (180 - angle);
		}
	}
	else
	{
		if (to.row > from.row)
		{
			return (180 + angle);
		}
		else
		{
			return (angle);
		}
	}
}

double WaypointManager::calculateIncline(Cell from, Cell to)
{
	isVerticle = 0;
	if(from.col == to.col)
	{
		isVerticle = 1;
		return(9999);
	}
	else
	{
		return((to.row - from.row) / (to.col - from.col));
	}
}

void WaypointManager::setNextWaypoint(Waypoint next)
{
	currWaypoint.point = nextWaypoint.point;
	currWaypoint.yaw = nextWaypoint.yaw;

	nextWaypoint.point = next.point;
	nextWaypoint.yaw = next.yaw;
}


bool WaypointManager::isInWaypoint(double x,double y)
{
	double dx = nextWaypoint.point.x - x;
	double dy = nextWaypoint.point.y - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	cout << "Next way point x: "<< nextWaypoint.point.x << " ---> current x: " << x << endl;
	cout << "Next way point y: "<< nextWaypoint.point.y << " ---> current y: " << y << endl;
	cout << "Next way point yaw" << nextWaypoint.yaw <<  endl;
	cout << "Distance to next way point: " << (distance) << endl;
	cout << endl;

	// Checking if the robot hit the way point, considering tolerance
	if (distance*gridResolution <= 10)
	{
		return true;
	}
	return false;
}


WaypointManager::~WaypointManager() {
	// TODO Auto-generated destructor stub
}

