#include <stdio.h>
#include <math.h>
#include <string.h>

#include "resourcetrack.h"

// calculation result
struct CalcResult{
    float power;
    float cn2;
    float cnlogn;
    float cn;
};
// raw data about resource consumption
struct Resource
{
    unsigned int size;
    unsigned long time;
    unsigned long space;
    struct CalcResult* calcResult;
};

const char* target;

void printList(const List l)
{
    ListPosition p = List_header(l);

    if (List_isEmpty(l))
        printf("Empty list\n");
    else
    {
        do
        {
            p = List_advance(p);
            struct Resource* res = (struct Resource*) List_retrieve(p);
            printf("(%d, %ld, %ld)  ",res->size,res->time, res->space);
        }
        while (!List_isLast(p, l));
        printf("\n");
    }
}

void Resource_startTrack(const char* msg)
{
    printf("Start tracking time/space usage for %s\n", msg);
    target = msg;
    totalTime = 0;
    totalSpace = 0;
    if(resourceList!=NULL)
        List_deleteList(resourceList);
    resourceList = List_makeEmpty(NULL);
}

void Resource_logTime(unsigned long time)
{
    totalTime += time;
}

void Resource_logSpace(int space)
{
    totalSpace += space;
}

ListPosition position=NULL;

void Resource_storeData(unsigned int size)
{
    if(position==NULL)
        position = List_header(resourceList);
    struct Resource* res = malloc( sizeof( struct Resource ) );
    res->size = size;
    res->time = totalTime;
    res->space = totalSpace;
    List_insert(res, resourceList, position);
    position = List_advance(position);

    //clear
    totalTime = 0;
    totalSpace = 0;
}

//analytical results
void Resource_analyseSequence()
{

//    printList(resourceList);

    ListPosition p = List_header(resourceList);
    if (List_isEmpty(resourceList))
    {
        printf("Empty list\n");
        return;
    }

    // ----------analyse raw data of one test, calc mean of constants------------
    int count = 0;
    const struct CalcResult INITILIZED = {0.0,0.0,0.0,0.0};
    struct CalcResult sum = INITILIZED;
    struct CalcResult mean = INITILIZED;
    struct CalcResult sumDeviation = INITILIZED;
    struct CalcResult deviation = INITILIZED;

    do
    {
        p = List_advance(p);
        //calc data
        struct Resource* res = (struct Resource*) List_retrieve(p);
        struct CalcResult* calcRet = Resource_analyse(res->size, res->time, res->space);
        printf("(%d, %ld, %ld) (%f, %f, %f, %f) \n",res->size,res->time, res->space, calcRet->power, calcRet->cn2, calcRet->cnlogn, calcRet->cn);
        res->calcResult = calcRet;

        //sum of constants
        sum.cn2 += calcRet->cn2;
        sum.cnlogn += calcRet->cnlogn;
        sum.cn += calcRet->cn;
        count ++;
    }
    while (!List_isLast(p, resourceList));

    // mean
    mean.cn2 =  sum.cn2 / count;
    mean.cnlogn = sum.cnlogn / count;
    mean.cn = sum.cn / count;
    printf("cn2 mean = %f, cnlogn mean = %f, cn mean = %f\n",mean.cn2, mean.cnlogn, mean.cn);

    // ---------Calc variance of constants-----------
    p = List_header(resourceList);
    // open file
    char data[50];
    char filePath[50] = "./plot/";
    strcat(filePath, target);
    strcat(filePath, ".dat");
    FILE *dataFile = fopen(filePath, "w+");
    do
    {
        // sum variance
        p = List_advance(p);
        struct Resource* res = (struct Resource*) List_retrieve(p);
        struct CalcResult* ret = res->calcResult;
        sumDeviation.cn2 += pow((ret->cn2 - mean.cn2),2) / count;
        sumDeviation.cnlogn += pow((ret->cnlogn - mean.cnlogn),2) / count;
        sumDeviation.cn += pow((ret->cn - mean.cn),2) / count;
//        printf(" cnlogn: %f = , sum = %f\n",pow((ret->cnlogn - mean.cnlogn),2) / count, sumDeviation.cnlogn);
        // write to data file
        sprintf(data, "%d  %lu\n", res->size, res->time);
        fputs(data, dataFile);
    }
    while (!List_isLast(p, resourceList));
    fclose(dataFile);

    // deviation
    deviation.cn2 = sqrt(sumDeviation.cn2);
    deviation.cnlogn = sqrt(sumDeviation.cnlogn);
    deviation.cn = sqrt(sumDeviation.cn);
    printf("standard deviation of c n2 = %f, c nlogn = %f, c n = %f\n", deviation.cn2, deviation.cnlogn, deviation.cn);
}

struct CalcResult* Resource_analyse(unsigned int size, unsigned long time, unsigned long space)
{

//    printf("\ttotal time used: %ld against input size: %d\n", time, size);
    struct CalcResult* ret = malloc( sizeof( struct CalcResult ) );

    // ---------------time-----------------
    float power = 0.0F;
    power = log((float)time) / log((float)size);
//    printf("\trunning time = size^%f\n",power);
    ret->power = power;

    long n2 =  size * size;
    long nlogn = size * log2((float)size);
    float c = (float)time / (float)n2;
//    printf("\trunning time = %f * n^2\n",c);
    ret->cn2 = c;

    c = (float)time / (float)nlogn;
//    printf("\trunning time = %f * n * log(n)\n",c);
    ret->cnlogn = c;

    c = (float)time / (float)size;
    ret->cn = c;

    // -------------space -----------------
    power = log10((float)space) / log10((float)size);
//    printf("\tspace = size^%f\n", power);

//    printf("\ttotal space used: %d against input size: %d\n", space, size);
    c = (float)space / (float)size;
//    printf("\tspace = %f * n\n",c);

    return ret;
}

/*
void Resource_analyse(unsigned int size)
{

    printf("\ttotal time used: %ld against input size: %d\n", totalTime, size);

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
*/
