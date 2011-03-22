#include <stdio.h>

#include "resource-track.h"

void Resource_logTime(unsigned long time){
	totalTime += time;
}

void Resource_print(){
    printf("Total time used: %d\n", totalTime);
}


