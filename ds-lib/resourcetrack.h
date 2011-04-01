/*
 * resource-track.h
 *
 *  Created on: Mar 22, 2011
 *      Author: nan
 */

#ifndef RESOURCE_TRACK_H_
#define RESOURCE_TRACK_H_

#include <time.h>

#include "list.h"

unsigned long totalTime;
long totalSpace;
long maxSpace;
List resourceList;

void Resource_startTrack(const char* msg);
void Resource_logTime(unsigned long time);
void Resource_logSpace(int space);
void Resource_clearData();
void Resource_storeData(unsigned int size);
struct CalcResult* Resource_analyse(unsigned int size, unsigned long time, long space);
void Resource_analyseSequence();
#endif /* RESOURCE_TRACK_H_ */
