#ifndef __CALC_H
#define __CALC_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define NUM_DIMENSIONS 2
typedef struct Particle{
	double x[NUM_DIMENSIONS];
	double p[NUM_DIMENSIONS];
} Particle;
typedef struct Frame{
	Particle *particles;
} Frame;

extern Frame* buffer;
extern double *mass;

extern unsigned numParticles;
extern const unsigned CALCULATIONS_PER_SECOND;
extern const unsigned NUM_FRAMES;

extern const double G;
extern const double DT;
extern const double _H;

double computeHamiltonian(Frame *f);
void calculateParticles();
void initializeParticles();
void createParticles();
void destroyParticles();

#endif
