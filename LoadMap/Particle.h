/*
 * Particle.h
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Map.h"
#include "Robot.h"
#include "math.h"
#define NORMALIZE_FACTOR 1.2
#define TOP_DISTANCE 0.2
#define TOP_DELTA_TETA 0.01
#define TRH_DIS 2
#define TRH_YAW 2
class Particle
{
	private:
	Point point;
	double teta;
	double belief;

	public:
	Particle(Point point, double dYaw);
	double getBelief();
	void paint(Map* map);
	void unpaint(Map* map);

	double update(Point deltaPoint, double deltaTeta , LaserProxy* laser);
	double probabibilityMove(Point deltaPoint, double deltaTeta);
	virtual ~Particle();
};
#endif /* PARTICLE_H_ */
