#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "resourcetrack.h"

// calculation result
struct CalcResult{
    float power;
    float cn2;
    float cnlogn;
    float cn;
    float c1;

    float cn2Space;
    float cnlognSpace;
    float cnSpace;
};
// raw data about resource consumption
struct Resource
{
    unsigned int size;
    unsigned long time;
    long space;
    struct CalcResult* calcResult;
};

const char* target;

clock_t startTime;
clock_t endTime;

bool logAllowed = true;

void printList(const List l)
{
    logAllowed = false;
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
    logAllowed = true;
}

void Resource_startTrack(const char* msg)
{
    printf("Start tracking time/space usage for %s\n", msg);
    Resource_clearData();
    target = msg;

    startTime = clock();

    logAllowed = false;
    if(resourceList!=NULL){
        List_deleteList(resourceList);
    }
    resourceList = List_makeEmpty(NULL);
    logAllowed = true;
}

void Resource_logTime(unsigned long time)
{
    if(logAllowed)
        totalTime += time;
}

void Resource_logSpace(int space)
{
    if(logAllowed){
       // printf("space logged: %d\n", space);
        totalSpace += space;
        if(totalSpace>maxSpace)
            maxSpace = totalSpace;
    }
}

ListPosition position=NULL;

void Resource_clearData(){
    totalTime = 0;
//    printf("clear totalSpace = %d\n", totalSpace);
    totalSpace = 0;
    maxSpace = 0;
    logAllowed = true;
}

void Resource_storeData(unsigned int size)
{
    logAllowed = false;
    if(position==NULL)
        position = List_header(resourceList);

    struct Resource* res = (struct Resource *)malloc( sizeof( struct Resource ) );
    res->size = size;
    // time
    res->time = totalTime;
    /*
    long diff = (clock() - startTime) *1000 / CLOCKS_PER_SEC;
    res->time = diff;
    printf("now = %ld, startTime = %ld, diff = %ld, CLOCKS_PER_SEC = %ld\n", clock(),startTime, diff, CLOCKS_PER_SEC);
    */
    // space
//    struct mstats* mem = mstats();
//    printf("bytes used: %d\n",mem);
    if(maxSpace>0)
        res->space = maxSpace;
    else
        res->space = totalSpace;


    List_insert(res, resourceList, position);
    position = List_advance(position);

    //clear
    Resource_clearData();
}

//analytical results
void Resource_analyseSequence()
{
    logAllowed = false;

    ListPosition p = List_header(resourceList);
    if (List_isEmpty(resourceList))
    {
        printf("Empty list\n");
        logAllowed = true;
        return;
    }

    // ----------analyse raw data of one test, calc mean of constants------------
    int count = 0;
    const struct CalcResult INITILIZED = {0.0,0.0,0.0,0.0,0.0};
    struct CalcResult sum = INITILIZED;
    struct CalcResult mean = INITILIZED;
    struct CalcResult sumDeviation = INITILIZED;
    struct CalcResult deviation = INITILIZED;


    unsigned long lastTime =  0l;
    long lastSpace = 0l;
    bool constant = true;
    bool constantSpace = true;
    do
    {
        p = List_advance(p);

        //calc data
        struct Resource* res = (struct Resource*) List_retrieve(p);
        if(count ==0){
            lastTime = res->time;
            lastSpace = res->space;
        }
        struct CalcResult* calcRet = Resource_analyse(res->size, res->time, res->space);
        printf("(%d, %ld, %ld) (%f, %f, %f, %f\t %f, %f, %f) \n",res->size,res->time, res->space, calcRet->power, calcRet->cn2, calcRet->cnlogn, calcRet->cn, calcRet->cn2Space, calcRet->cnlognSpace, calcRet->cnSpace);
        res->calcResult = calcRet;

        //sum of constants
        sum.cn2 += calcRet->cn2;
        sum.cnlogn += calcRet->cnlogn;
        sum.cn += calcRet->cn;
        sum.cn2Space += calcRet->cn2Space;
        sum.cnlognSpace += calcRet->cnlognSpace;
        sum.cnSpace += calcRet->cnSpace;

        // constant time/space check
        constant &= (res->time == lastTime);
        constantSpace &=(res->space == lastSpace);

        // update vars
        lastTime = res->time;
        count ++;
    }
    while (!List_isLast(p, resourceList));

    if(constant && constantSpace){
        printf("constant time & space! constant time = %ld, constant space = %ld\n", lastTime,lastSpace);
        return;
    }

    // mean
    mean.cn2 =  sum.cn2 / count;
    mean.cnlogn = sum.cnlogn / count;
    mean.cn = sum.cn / count;
    mean.cn2Space = sum.cn2Space / count;
    mean.cnlognSpace = sum.cnlognSpace / count;
    mean.cnSpace = sum.cnSpace / count;
    printf("Constant means: cn2 = %.2f, cnlogn = %.2f, cn = %.2f \t cn2 space = %.2f, cnlogn space = %.2f, cn space = %.2f\n",mean.cn2, mean.cnlogn, mean.cn, mean.cn2Space, mean.cnlognSpace, mean.cnSpace);

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
        sumDeviation.cn2Space += pow((ret->cn2Space - mean.cn2Space),2) / count;
        sumDeviation.cnlognSpace += pow((ret->cnlognSpace - mean.cnlognSpace),2) / count;
        sumDeviation.cnSpace += pow((ret->cnSpace - mean.cnSpace),2) / count;

//        printf(" cnlogn: %f = , sum = %f\n",pow((ret->cnlogn - mean.cnlogn),2) / count, sumDeviation.cnlogn);
        // write to data file
        sprintf(data, "%d  %lu  %ld\n", res->size, res->time, res->space);
        fputs(data, dataFile);
    }
    while (!List_isLast(p, resourceList));
    fclose(dataFile);

    // deviation
    deviation.cn2 = sqrt(sumDeviation.cn2)/mean.cn2*100;
    deviation.cnlogn = sqrt(sumDeviation.cnlogn)/mean.cnlogn*100;
    deviation.cn = sqrt(sumDeviation.cn)/mean.cn*100;
    deviation.cn2Space = fabs(sqrt(sumDeviation.cn2Space) /mean.cn2Space * 100);
    deviation.cnlognSpace = fabs(sqrt(sumDeviation.cnlognSpace)/mean.cnlognSpace*100);
    deviation.cnSpace = fabs(sqrt(sumDeviation.cnSpace)/mean.cnSpace*100);

    printf("Relative standard deviation: c n2 = %.2f%, c nlogn = %.2f%, c n = %.2f% \t c n2 space = %.2f%, cnlogn space = %.2f%, cn space = %.2f%\n", deviation.cn2, deviation.cnlogn, deviation.cn, deviation.cn2Space, deviation.cnlognSpace, deviation.cnSpace);
    logAllowed = true;
}

struct CalcResult* Resource_analyse(unsigned int size, unsigned long time, long space)
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
//    power = log((float)space) / log((float)size);
//    printf("\tspace = size^%f\n", power);

    c = (float)space / (float)n2;
//    printf("\tspace = %f * n^2\n",c);
    ret->cn2Space = c;

    c = (float)space / (float)nlogn;
//    printf("\tspace = %f * n * log(n)\n",c);
    ret->cnlognSpace = c;

    c = (float)space / (float)size;
    ret->cnSpace = c;

    return ret;
}
