#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "definitions.h"

unsigned numParticles;
Frame* buffer;
double *mass;

const unsigned CALCULATIONS_PER_SECOND = 1000;
const unsigned NUM_FRAMES = 30*CALCULATIONS_PER_SECOND;
const double G = 1500;

const double DT = 1/((double)CALCULATIONS_PER_SECOND);
const double _H = 0.000001;

double computeHamiltonian(Frame f){
	double hamiltonian = 0;
	//kinetic
	for(unsigned j=0;j<numParticles;j++)
		hamiltonian += (f.particles[j].p[0]*f.particles[j].p[0]+f.particles[j].p[1]*f.particles[j].p[1])/(2*mass[j]);
	
	//gravity
	for(unsigned j=0;j<numParticles;j++){
		for(unsigned k=0;k<numParticles;k++){
			if(j == k)
				continue;
			hamiltonian -= G*mass[j]*mass[k]/sqrt(
			(f.particles[j].x[0]-f.particles[k].x[0])*(f.particles[j].x[0]-f.particles[k].x[0])+
			(f.particles[j].x[1]-f.particles[k].x[1])*(f.particles[j].x[1]-f.particles[k].x[1])
			);
		}
	}
	return hamiltonian;
}

void calculateParticles(){
	for(unsigned i=0; i<NUM_FRAMES-1;i++){
		Frame current = buffer[i];
		double hc = computeHamiltonian(current);
		for(unsigned j=0; j<numParticles;j++){
			for(int c=0;c<2;c++){
				// dq/dt=dh/dp
				// dp/dt=-dh/dq
				current.particles[j].p[c] += _H;
				double hn = computeHamiltonian(current);
				current.particles[j].p[c] -= _H;
				buffer[i+1].particles[j].x[c] = buffer[i].particles[j].x[c] + (hn - hc)/_H*DT;
				current.particles[j].x[c] += _H;
				hn = computeHamiltonian(current);
				current.particles[j].x[c] -= _H;
				buffer[i+1].particles[j].p[c] = buffer[i].particles[j].p[c] - (hn - hc)/_H*DT;
			}
		}
	}
}

void initializeParticles(){
	mass[0] = 1000;//
	buffer[0].particles[0].x[0] = 300;//
	buffer[0].particles[0].x[1] = 300;//
	buffer[0].particles[0].p[0] = 0;//
	buffer[0].particles[0].p[1] = 0;//
	int k=50;
	for(unsigned j=1/**/;j<numParticles;j++){
		buffer[0].particles[j].x[0] = 300-k+rand() % (2*k);
		buffer[0].particles[j].x[1] = 300-k+rand() % (2*k);
		double x=buffer[0].particles[j].x[0]-300,y=buffer[0].particles[j].x[1]-300;
		double r = sqrt(x*x+y*y);
		double theta = atan2(y,x);
		double v0 = sqrt(2*G*mass[0]/r);
		buffer[0].particles[j].p[0] = -v0*sin(theta);
		buffer[0].particles[j].p[1] = v0*cos(theta);
		mass[j] = 1;
	}
}

void createParticles(){
	numParticles = 16;
	buffer = (Frame*)malloc(NUM_FRAMES*sizeof(Frame));
	mass = (double*)malloc(numParticles*sizeof(double));
	for(unsigned i=0; i<NUM_FRAMES;i++)
		buffer[i].particles = (Particle*)malloc(numParticles*sizeof(Particle));
}

void destroyParticles(){
	for(unsigned i=0; i<NUM_FRAMES;i++)
		free(buffer[i].particles);
	free(buffer);
	free(mass);
}
