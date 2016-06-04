/*
 * ParticleFilter.h
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#ifndef PARTICLEFILTER_H_
#define PARTICLEFILTER_H_
#include "Map.h"

typedef struct particle
{
	point cordinate;
	double weight;
	char state;
}
Particle;

class ParticleFilter {
public:
	ParticleFilter();
	virtual ~ParticleFilter();
};

#endif /* PARTICLEFILTER_H_ */
