/* This file contains a collection of sorting routines */
#include <stdlib.h>
#include <math.h>

#include "fatal.h"
#include "sort.h"
#include "resourcetrack.h"

//------------------------radix sort--------------------------------------
void printArray(ElementType a[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(", a[%d]=%d", i, a[i]);
	}
	printf("\n");
}

int getBit(ElementType element, int bit) {
	int divider = pow(10, bit);
	int mod = pow(10, bit + 1);
	int reminder = element % mod;
	int ret = reminder / divider;
	return ret;
}

int partition(ElementType a[], int bit, int left, int right) {
	int leftBit, rightBit;
	//FIXME! remove the hard coding
	//    printArray(a,10);
	while (left != right) {
		while ((leftBit = getBit(a[left], bit)) == 0 && left < right)
			left++;
		while ((rightBit = getBit(a[right], bit)) == 1 && left < right)
			right--;
		// swap left & right
		int tmp = a[left];
		a[left] = a[right];
		a[right] = tmp;
		printArray(a, 10);
	}
	rightBit = getBit(a[right], bit);
	if (rightBit == 0)
		right++;
	//    printArray(a,10);
	return right;
}

void radixExchangeSort(ElementType a[], int bit, int left, int right) {
	int split = partition(a, bit, left, right);
	if (bit > 0) {
		int range = split - 1 - left + 1;
		if (range > 1)
			radixExchangeSort(a, bit - 1, left, split - 1);
		range = right - split + 1;
		if (range > 1)
			radixExchangeSort(a, bit - 1, split, right);
	}
}
//------------------------radix sort--------------------------------------

void Swap(ElementType *Lhs, ElementType *Rhs) {
	ElementType Tmp = *Lhs;
	*Lhs = *Rhs;
	*Rhs = Tmp;
	Resource_logTime(7);
}

/* START: fig7_2.txt */
void insertionSort(ElementType A[], int N) {
    Resource_logSpace(N);
	int j, P;
	ElementType Tmp;

	for (P = 1; P < N; P++) {
		Tmp = A[P];
		Resource_logTime(3);
		for (j = P; j > 0 && A[j - 1] > Tmp; j--){
			A[j] = A[j - 1];
			Resource_logTime(7); // 5 steps in for loop, 2 steps of retriving data from array & assign
		}
		A[j] = Tmp;
		Resource_logTime(1);
	}
}
/* END */

/* START: fig7_4.txt */
void shellsort(ElementType A[], int N) {
	int i, j, Increment;
	ElementType Tmp;

	/* 1*/for (Increment = N / 2; Increment > 0; Increment /= 2)
		/* 2*/for (i = Increment; i < N; i++) {
			/* 3*/Tmp = A[i];
			/* 4*/
			for (j = i; j >= Increment; j -= Increment)
				/* 5*/if (Tmp < A[j - Increment])
					/* 6*/A[j] = A[j - Increment];
				else
					/* 7*/break;
			/* 8*/A[j] = Tmp;
		}
}
/* END */

/* START: fig7_8.txt */

#define LeftChild( i )  ( 2 * ( i ) + 1 )

void PercDown(ElementType A[], int i, int N) {
	int Child;
	ElementType Tmp;

	for (Tmp = A[i]; LeftChild( i ) < N; i = Child) {
		Resource_logTime(3);

		Child = LeftChild( i );
		Resource_logTime(3);

		Resource_logTime(7);
		if (Child != N - 1 && A[Child + 1] > A[Child]){
            Child++;
            Resource_logTime(1);
		}

		Resource_logTime(2);
		if (Tmp < A[Child]){
			A[i] = A[Child];
			Resource_logTime(2);
		}
		else
			break;
	}
	A[i] = Tmp;
	Resource_logTime(1);
}

void heapsort(ElementType A[], int N) {
	int i;
    Resource_logSpace(N);

	for (i = N / 2; i >= 0; i--){ /* BuildHeap */
	    Resource_logTime(2);
		PercDown(A, i, N);
	}
	for (i = N - 1; i > 0; i--) {
		Resource_logTime(2);
		Swap(&A[0], &A[i]); /* DeleteMax */
		PercDown(A, 0, i);
	}
}
/* END */

/* START: fig7_10.txt */
/* Lpos = start of left half, Rpos = start of right half */

void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos,
		int RightEnd) {
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	/* main loop */
	while (Lpos <= LeftEnd && Rpos <= RightEnd)
		if (A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];

	while (Lpos <= LeftEnd) /* Copy rest of first half */
		TmpArray[TmpPos++] = A[Lpos++];
	while (Rpos <= RightEnd) /* Copy rest of second half */
		TmpArray[TmpPos++] = A[Rpos++];

	/* Copy TmpArray back */
	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];
}
/* END */

/* START: fig7_9.txt */
void MSort(ElementType A[], ElementType TmpArray[], int Left, int Right) {
	int Center;

	if (Left < Right) {
		Center = (Left + Right) / 2;
		MSort(A, TmpArray, Left, Center);
		MSort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
}

void mergesort(ElementType A[], int N) {
	ElementType *TmpArray;

	TmpArray = malloc(N * sizeof(ElementType));
	if (TmpArray != NULL) {
		MSort(A, TmpArray, 0, N - 1);
		free(TmpArray);
	} else
		fatalError( "No space for tmp array!!!" );
}
/* END */

/* START: fig7_13.txt */
/* Return median of Left, Center, and Right */
/* Order these and hide the pivot */

ElementType Median3(ElementType A[], int Left, int Right) {
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	/* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */

	Swap(&A[Center], &A[Right - 1]); /* Hide pivot */
	return A[Right - 1]; /* Return pivot */
}
/* END */

/* START: fig7_14.txt */
#define Cutoff ( 3 )

void Qsort(ElementType A[], int Left, int Right) {
	int i, j;
	ElementType Pivot;

	/* 1*/if (Left + Cutoff <= Right) {
		/* 2*/Pivot = Median3(A, Left, Right);
		/* 3*/
		i = Left;
		j = Right - 1;
		/* 4*/
		for (;;) {
			/* 5*/while (A[++i] < Pivot) {
			}
			/* 6*/
			while (A[--j] > Pivot) {
			}
			/* 7*/if (i < j)
				/* 8*/Swap(&A[i], &A[j]);
			else
				/* 9*/break;
		}
		/*10*/
		Swap(&A[i], &A[Right - 1]); /* Restore pivot */

		/*11*/
		Qsort(A, Left, i - 1);
		/*12*/Qsort(A, i + 1, Right);
	} else
		/* Do an insertion sort on the subarray */
		/*13*/insertionSort(A + Left, Right - Left + 1);
}
/* END */

/* This code doesn't work; it's Figure 7.15. */
#if 0
/* START: fig7_15.txt */
/* 3*/i = Left + 1; j = Right - 2;
/* 4*/for(;; )
{
	/* 5*/while( A[ i ] < Pivot ) i++;
	/* 6*/while( A[ j ] > Pivot ) j--;
	/* 7*/if( i < j )
	/* 8*/Swap( &A[ i ], &A[ j ] );
	else
	/* 9*/break;
}
/* END */
#endif

/* START: fig7_12.txt */
void quicksort(ElementType A[], int N) {
	Qsort(A, 0, N - 1);
}
/* END */

/* START: fig7_16.txt */
/* Places the kth smallest element in the kth position */
/* Because arrays start at 0, this will be index k-1 */
void Qselect(ElementType A[], int k, int Left, int Right) {
	int i, j;
	ElementType Pivot;

	/* 1*/if (Left + Cutoff <= Right) {
		/* 2*/Pivot = Median3(A, Left, Right);
		/* 3*/
		i = Left;
		j = Right - 1;
		/* 4*/
		for (;;) {
			/* 5*/while (A[++i] < Pivot) {
			}
			/* 6*/
			while (A[--j] > Pivot) {
			}
			/* 7*/if (i < j)
				/* 8*/Swap(&A[i], &A[j]);
			else
				/* 9*/break;
		}
		/*10*/
		Swap(&A[i], &A[Right - 1]); /* Restore pivot */

		/*11*/if (k <= i)
			/*12*/Qselect(A, k, Left, i - 1);
		/*13*/else if (k > i + 1)
			/*14*/Qselect(A, k, i + 1, Right);
	} else
		/* Do an insertion sort on the subarray */
		/*15*/insertionSort(A + Left, Right - Left + 1);
}
/* END */

/* ROUTINES TO TEST THE SORTS */

void Permute(ElementType A[], int N) {
	int i;

	for (i = 0; i < N; i++)
		A[i] = i;
	for (i = 1; i < N; i++)
		Swap(&A[i], &A[rand() % (i + 1)]);
}

void Checksort(ElementType A[], int N) {
	int i;
	for (i = 0; i < N; i++)
		if (A[i] != i)
			printf("Sort fails: %d %d\n", i, A[i]);
	printf("Check completed\n");
}

void Copy(ElementType Lhs[], const ElementType Rhs[], int N) {
	int i;
	for (i = 0; i < N; i++)
		Lhs[i] = Rhs[i];
}

void reverseCopy(ElementType lhs[], const ElementType rhs[], int n){
    int i;
	for (i = 0; i < n; i++)
		lhs[i] = rhs[n-i-1];

}

#define MaxSize 7000
int Arr1[MaxSize];
int Arr2[MaxSize];
int arr3[MaxSize];

void Sort_test() {
	int i;

	// test radix exchange sort
	//	printf("test radix exchange sort\n");
	//	int array[10] = { 10, 111, 110, 101, 111, 11, 110, 101, 0, 111 };
	//	printArray(array,10);
	//	radixExchangeSort(array, 2, 0, 9);

	Permute(Arr2, MaxSize);
    Resource_startTrack("insertion-sort");
	for(i=10;i<=1000;i+=10){
        Copy(Arr1, Arr2, i);
        insertionSort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();

	Resource_startTrack("insertion-sort-best-case");
	for(i=10;i<=1000;i+=10){
        insertionSort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();


	reverseCopy(arr3, Arr1, MaxSize);
	Resource_startTrack("insertion sort (worst case)");
	insertionSort(arr3, MaxSize);

    Copy(Arr1, Arr2, MaxSize);
	Resource_startTrack("heap sort");
	heapsort(Arr1, MaxSize);


/*
	for (i = 0; i < 10; i++) {
		Permute(Arr2, MaxSize);
		Copy(Arr1, Arr2, MaxSize);
		insertionSort(Arr1, MaxSize);
		Checksort(Arr1, MaxSize);

		Copy(Arr1, Arr2, MaxSize);
		shellsort(Arr1, MaxSize);
		Checksort(Arr1, MaxSize);

		Copy(Arr1, Arr2, MaxSize);
		heapsort(Arr1, MaxSize);
		Checksort(Arr1, MaxSize);

		Copy(Arr1, Arr2, MaxSize);
		mergesort(Arr1, MaxSize);
		Checksort(Arr1, MaxSize);

		Copy(Arr1, Arr2, MaxSize);
		quicksort(Arr1, MaxSize);
		Checksort(Arr1, MaxSize);

		Copy(Arr1, Arr2, MaxSize);
		Qselect(Arr1, MaxSize / 2 + 1 + i, 0, MaxSize - 1);
		if (Arr1[MaxSize / 2 + i] != MaxSize / 2 + i)
			printf("Select error: %d %d\n", MaxSize / 2 + i,
					Arr1[MaxSize / 2 + i]);
		else
			printf("Select works\n");
	}
*/
}

