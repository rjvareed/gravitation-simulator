#define NUM_DIMENSIONS 2
typedef struct Particle{
	double x[NUM_DIMENSIONS];
	double p[NUM_DIMENSIONS];
} Particle;
typedef struct Frame{
	Particle *particles;
} Frame;
