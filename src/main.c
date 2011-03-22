/*
 ============================================================================
 Name        : main.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include "../ds-lib/testlist.h"
#include "../ds-lib/testque.h"
#include "../ds-lib/testtree.h"
#include "../ds-lib/sort.h"

int main(void) {
//    int c[10];
//    int* b[10];
//
//
//    int** a=&b[0];
//
//    a[4][4]= 3;
//    int a[10][10][10];

    /*
    int x,y,z;
    for(x=0;x<10;x++)
        for(y=0;y<10;y++)
            for(z=0;z<10;z++)
                a[x][y][z]=x*100+y*10+z;

    printf("-----------------Test Array-------------------\n");
    printf("a5,5,5 =  %d\n",a[5][5][5]);
    */
//////    //a[0]=*(a+5);
//////    //&my_array[0]
////////    a[0] = &a[5];
//////    int*[][] b = &a[5];
//////    printf("b-1,-1,-1 =  %d\n",a[-1][-1][-1]);



	int i;
	int value;
	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	struct tms st_cpu;
	struct tms en_cpu;
	clock_t st_time, en_time;
	st_time = times(&st_cpu);

	printf("-----------------Test Tree-------------------\n");
	Tree_test();

	printf("-----------------Test List-------------------\n");
	List_Test();

	printf("-----------------Test Queue------------------\n");
	Queue_Test();

	printf("-----------------Test Sorting------------------\n");
	Sort_Test();
//	for( i = 0; i < 500000; i++ )
//		value = 5000*8000;
	sleep(1);
	en_time = times(&en_cpu);

	//long int elapsed = end - start;
//	printf("start %d \n", start);
//	printf("end %d \n", end);
//	printf("time elapsed: %d \n", elapsed);

	printf("Real Time: %jd, User Time %jd, System Time %jd\n",
	        (long int)(en_time - st_time),
	        (long int)(en_cpu.tms_utime - st_cpu.tms_utime),
	        (long int)(en_cpu.tms_stime - st_cpu.tms_stime));

	return EXIT_SUCCESS;
}
