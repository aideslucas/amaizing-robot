/*
 * ParticleFilter.h
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#ifndef PARTICLEFILTER_H_
#define PARTICLEFILTER_H_
#include <list>
#include "Particle.h"
using namespace std;
#define THRESHOLD 0.25
#define STANDARD 0.7
#define MAX_PARTICLES_NUM 100
#define MIN_PARTICLES_NUM 1
#define PARTICLE_RANGE 0.3
#define PARTICLE_NUM_TO_CREATE 5

class ParticleFilter {
private:
list<Particle> arrParticles;
void createChildren(Point point, double range, int numOfParticles);

public:
	ParticleFilter();
	void update(Point point, double teta, Point deltaPoint,	double deltaTeta, LaserProxy* pLaserProxy);
	Particle* getHighestProbParticle();
	virtual ~ParticleFilter();
};

#endif /* PARTICLEFILTER_H_ */
