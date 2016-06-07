/*
 * Waypoint.h
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_
#include "limits.h"
#include "Map.h"
class Waypoint {
public:
	Point point;
	double yaw;

	Waypoint();
	Waypoint(Point point, double yaw);

	void operator()(Point point, double yaw)
	{
		this->point.x = point.x;
		this->point.y = point.y;
		this->yaw = yaw;
	}
	bool operator<(const Waypoint& wp) const
	{
		return (this->point.y*INT_MAX + this->point.x < wp.point.y*INT_MAX + wp.point.x);
	}
	void operator=(const Waypoint& wp)
	{
		this->point.x = wp.point.x;
		this->point.y = wp.point.y;
		this->yaw = wp.yaw;
	}
	bool operator==(const Waypoint& wp) const
	{
		return (this->point.y == wp.point.y && this->point.x == wp.point.x);
	}
	bool operator!=(const Waypoint& wp) const
	{
		return (this->point.y != wp.point.y || this->point.x != wp.point.x);
	}


	virtual ~Waypoint();
};

#endif /* WAYPOINT_H_ */
