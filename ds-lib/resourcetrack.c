#include <stdio.h>
#include <math.h>

#include "resourcetrack.h"

void Resource_startTrack(const char* msg) {
	printf("Start tracking time/space usage for %s\n", msg);
	totalTime = 0;
	totalSpace = 0;
}

void Resource_logTime(unsigned long time) {
	totalTime += time;
}

void Resource_logSpace(int space){
    totalSpace += space;
}

//float log2(float n){
//    return log(n)/log(2);
//}
void Resource_analyse(unsigned int size) {
	printf("\ttotal time used: %d against input size: %d\n", totalTime, size);

	// time
	float power = 0.0F;
	power = log((float)totalTime) / log((float)size);
	printf("\trunning time = size^%f\n",power);

	long n2 =  size * size;
	long nlogn = size * log2((float)size);
	float c = (float)totalTime / (float)n2;
	printf("\trunning time = %f * n^2\n",c);
	c = (float)totalTime / (float)nlogn;
	printf("\trunning time = %f * n * log(n)\n",c);

    // space
	power = log10((float)totalSpace) / log10((float)size);
	printf("\tspace = size^%f\n",power);

	printf("\ttotal space used: %d against input size: %d\n", totalSpace, size);
	c = (float)totalSpace / (float)size;
	printf("\tspace = %f * n\n",c);
}

