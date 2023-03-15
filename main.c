#include <time.h>
#include "calc.h"
extern void start_gtk();

int main(int argc, char **argv){
	srand(time(NULL));
	createParticles();
	initializeParticles();
	calculateParticles();
	start_gtk();
	
	destroyParticles();
	return 0;
}
