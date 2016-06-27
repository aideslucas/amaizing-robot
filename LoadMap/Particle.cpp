/*
 * Particle.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#include "Particle.h"


Particle::Particle(Point point, double dYaw)
{
	this->point.x = point.x;
	this->point.y = point.y;
	this->teta = dYaw;
	this->belief = 1;
}

void Particle::paint(Map* map)
{
	for (int i = belief * -10; i < belief * 10; i++)
	{
		for (int j = belief * -10; j < belief * 10; j++)
		{
			if (i > 0 && j > 0 && i < map->getWidth() && j < map->getHeight())
			{
				Point p;
				p.x = point.x + j;
				p.y = point.y + i;
				map->paintCell(p, 0, 0, 255 * this->belief);
			}
		}
	}
}

void Particle::unpaint(Map* map)
{
	for (int i = belief * -10; i < belief * 10; i++)
		{
			for (int j = belief * -10; j < belief * 10; j++)
			{
				if (i > 0 && j > 0 && i < map->getWidth() && j < map->getHeight())
				{
					Point p;
					p.x = point.x + j;
					p.y = point.y + i;
					map->paintCell(p, 0, 0, 0);
				}
			}
		}
}


double Particle::update(Point deltaPoint, double deltaTeta , LaserProxy* laser)
{
	// Update the particle position
	this->point.x += deltaPoint.x;
	this->point.y += deltaPoint.y;
	this->teta += deltaTeta;

	// Guess the probability
	double byMove = probabibilityMove(deltaPoint, deltaTeta);
	this->belief = this->belief * byMove * NORMALIZE_FACTOR;

	if (this->belief > 1)
	{
		this->belief = 1;
	}

	return this->belief;
}

// Probability by move
double Particle::probabibilityMove(Point deltaPoint, double deltaTeta)
{
	double dist = sqrt(pow(deltaPoint.x, 2) + pow(deltaPoint.y, 2));
	double pro = 0;
	deltaTeta = abs(deltaTeta);

	if(dist > TRH_DIS && deltaTeta > TRH_YAW)
		pro = 0.2;

	if((dist < TRH_DIS && deltaTeta > TRH_YAW)||(dist > TRH_DIS && deltaTeta < TRH_YAW))
		pro = 0.4;

	if(dist < TRH_DIS && deltaTeta < TRH_YAW)
		pro = 0.8;

	if(dist < TRH_DIS && deltaTeta == 0)
		pro = 1;

	return pro;
}

double Particle::getBelief()
{
	return (this->belief);
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

