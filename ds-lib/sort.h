/*
 * sort.h
 *
 *  Created on: 12 Mar 2011
 *      Author: nan
 */

#ifndef SORT_H_
#define SORT_H_

typedef int ElementType;

void InsertionSort(ElementType A[], int N);
void Shellsort(ElementType A[], int N);
void Heapsort(ElementType A[], int N);
void Mergesort(ElementType A[], int N);
void Quicksort(ElementType A[], int N);
void radixExchangeSort(ElementType a[], int bit, int left, int right);

void Sort_Test();

#endif /* SORT_H_ */
