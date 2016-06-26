/*
 * ParticleFilter.cpp
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#include "ParticleFilter.h"

// Updates particles, deleting/creating/altering as needed
void ParticleFilter::update(Point point, double teta, Point deltaPoint, double deltaTeta, LaserProxy* pLaserProxy)
{
	// Initialize iterator
	list<Particle>::iterator iterator = arrParticles.begin();
	// Go over all the particles
	while (iterator != arrParticles.end())
	{
		// Calculate the belief
		double dBelief = iterator->update(deltaPoint, deltaTeta, pLaserProxy);
		list<Particle>::iterator tempIterator = iterator;
		tempIterator++;

		// Handle the belief
		if (dBelief < THRESHOLD && arrParticles.size() > MIN_PARTICLES_NUM)
		{
			arrParticles.erase(iterator);
		}
		else if (dBelief > STANDARD)
		{
			createChildren(point, PARTICLE_RANGE, PARTICLE_NUM_TO_CREATE);
		}

		// Copy the temp iterator
		iterator = tempIterator;
	}
}
// Creates new particles
void ParticleFilter::createChildren(Point point, double range, int numOfParticles)
{
	// Increase the size only if its below 100
	if(arrParticles.size() + numOfParticles < MAX_PARTICLES_NUM)
	{
		for(int i = 0; i < numOfParticles; ++ i)
		{
			// Creating random coordinates and yaw
			double randX = ((double) (rand() % 101) / 100.0) * range;
			double randY = ((double) (rand() % 101) / 100.0) * range;
			double randYaw = ((double) (rand() % 1000) / 1000.0);
			// Create new cell coordiante by new coordinates
			Point newPoint;
			newPoint.x = point.x + randX;
			newPoint.y = point.y + randY;
			arrParticles.push_front(Particle(newPoint, randYaw));
		}
	}
}

// Gets the particle with the highest probability
Particle* ParticleFilter::getHighestProbParticle()
{
	list<Particle>::iterator it;
	it = arrParticles.begin();
	Particle* particle = it.operator ->();
	for (it=arrParticles.begin(); it!=arrParticles.end(); ++it)
	{
		if (particle->getBelief() < it->getBelief())
		{
			particle = it.operator ->();
		}
	}

	return (particle);
}


ParticleFilter::ParticleFilter() {
	Point point;
	point.x = 0;
	point.y = 0;
	Particle* particle = new Particle(point, 0);

	arrParticles.push_front(*particle);
}

void ParticleFilter::paint(Map* map)
{
	list<Particle>::iterator it;
	Particle* particle;

	for (it=arrParticles.begin(); it!=arrParticles.end(); ++it)
	{
		particle = it.operator ->();
		particle->paint(map);
	}
}

ParticleFilter::~ParticleFilter() {
	// TODO Auto-generated destructor stub
}

