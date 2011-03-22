/*
 * resource-track.h
 *
 *  Created on: Mar 22, 2011
 *      Author: nan
 */

#ifndef RESOURCE_TRACK_H_
#define RESOURCE_TRACK_H_

static unsigned long totalTime;
static long totalSpace;

void Resource_startTrack(const char* msg);
void Resource_logTime(unsigned long time);
void Resource_logSpace(int space);
void Resource_analyse(unsigned int size);
#endif /* RESOURCE_TRACK_H_ */
