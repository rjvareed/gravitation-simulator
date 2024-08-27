#include <time.h>
#include "calc.h"
#include "drawing.h"

int main(int argc, char **argv){
	srand(time(NULL));
	createParticles();
	initializeParticles();
	calculateParticles();
	start_gtk();
	
	destroyParticles();
	return 0;
}
