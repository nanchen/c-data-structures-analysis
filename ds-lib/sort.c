/* This file contains a collection of sorting routines */
#include <stdlib.h>
#include <math.h>

#include "fatal.h"
#include "sort.h"
#include "resourcetrack.h"

const int SPACE_ELEMENT_INT =  sizeof(ElementType) + sizeof(int);
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
    const int SPACE = 2*sizeof(ElementType);
    Resource_logSpace(SPACE);

	ElementType Tmp = *Lhs; //2
	*Lhs = *Rhs; //3
	*Rhs = Tmp; //2
	Resource_logTime(9);
	Resource_logSpace(-SPACE);
}

/* START: fig7_2.txt */
void insertionSort(ElementType A[], int N) {
    //--------------space------------------------------
	const int SPACE = sizeof(ElementType) + sizeof(int);
	Resource_logSpace(SPACE);
    //--------------space------end---------------------

	int j, P;   // time = 2
	ElementType Tmp; // time = 1

	for (P = 1; P < N; P++) { // time = 3
		Tmp = A[P]; // time = 2
		for (j = P; j > 0 && A[j - 1] > Tmp; j--){ // time = 7
			A[j] = A[j - 1]; // time = 4
			Resource_logTime(11); // 7 steps in for loop, 4 steps of retriving data from array & assign
		}
		A[j] = Tmp; // time = 2
		Resource_logTime(7);
	}
	Resource_logTime(5);
	Resource_logSpace(-SPACE);
}
/* END */

/* START: fig7_4.txt */
void shellsort(ElementType A[], int N) {
	Resource_logSpace(SPACE_ELEMENT_INT);

	int i, j, Increment; // 3
	ElementType Tmp; // 1

    for (Increment = N / 2; Increment > 0; Increment /= 2){ // 3
   		Resource_logTime(3);
		for (i = Increment; i < N; i++) { // 3
			Tmp = A[i]; //2
			for (j = i; j >= Increment; j -= Increment){ // 3
				if (Tmp < A[j - Increment]){ // 3
					A[j] = A[j - Increment]; // 4
					Resource_logTime(4);
				}
				else{
					Resource_logTime(1);
					break; //1
				}
				Resource_logTime(6);
			}
			A[j] = Tmp; // 2
			Resource_logTime(7);
		}
    }
    Resource_logTime(6);
    Resource_logSpace(-SPACE_ELEMENT_INT);
}
/* END */

/* START: fig7_8.txt */

#define LeftChild( i )  ( 2 * ( i ) + 1 )

void PercDown(ElementType A[], int i, int N) {
    const int SPACE = sizeof(ElementType) + 2 * sizeof(int);
    Resource_logSpace(SPACE);

	int Child; //1
	ElementType Tmp; //1

	for (Tmp = A[i]; LeftChild( i ) < N; i = Child) { // 2
		Child = LeftChild( i ); //1

		if (Child != N - 1 && A[Child + 1] > A[Child]){ //7
            Child++; //2
            Resource_logTime(2);
		}

		if (Tmp < A[Child]){ //2
			A[i] = A[Child]; //3
			Resource_logTime(3);
		}
		else{
		    Resource_logTime(1);
			break;
		}
		Resource_logTime(10);
	}
	A[i] = Tmp; //2
	Resource_logTime(6);
	Resource_logSpace(-SPACE);
}

void heapsort(ElementType A[], int N) {
    Resource_logSpace(SPACE_ELEMENT_INT);

	int i; //1
	for (i = N / 2; i >= 0; i--){ /* BuildHeap */ //3
	    Resource_logTime(3);
		PercDown(A, i, N);
	}
	for (i = N - 1; i > 0; i--) { //3
		Resource_logTime(3);
		Swap(&A[0], &A[i]); /* DeleteMax */
		PercDown(A, 0, i);
	}
	Resource_logTime(3);
	Resource_logSpace(SPACE_ELEMENT_INT);
}
/* END */

/* START: fig7_10.txt */
/* Lpos = start of left half, Rpos = start of right half */

void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos,
		int RightEnd) {
	const int SPACE = 2* sizeof(ElementType) + 3*sizeof(int);
	Resource_logSpace(SPACE);

	int i, LeftEnd, NumElements, TmpPos; //4

	LeftEnd = Rpos - 1; //2
	TmpPos = Lpos; //1
	NumElements = RightEnd - Lpos + 1; //3

	/* main loop */
	while (Lpos <= LeftEnd && Rpos <= RightEnd){ //3

		if (A[Lpos] <= A[Rpos]) //3
			TmpArray[TmpPos++] = A[Lpos++]; //7
		else
			TmpArray[TmpPos++] = A[Rpos++];
        Resource_logTime(13);
	}

	while (Lpos <= LeftEnd){ /* Copy rest of first half */ //1
		TmpArray[TmpPos++] = A[Lpos++]; //7
		Resource_logTime(8);
	}
	while (Rpos <= RightEnd){ /* Copy rest of second half */ //1
		TmpArray[TmpPos++] = A[Rpos++]; //7
		Resource_logTime(8);
	}

	/* Copy TmpArray back */
	for (i = 0; i < NumElements; i++, RightEnd--){ //5
		A[RightEnd] = TmpArray[RightEnd]; //3
        Resource_logTime(8);
	}
	Resource_logTime(12);
	Resource_logSpace(-SPACE);
}
/* END */

/* START: fig7_9.txt */
void MSort(ElementType A[], ElementType TmpArray[], int Left, int Right) {
	const int SPACE = 2* sizeof(ElementType) + 2*sizeof(int);
	Resource_logSpace(SPACE);

	int Center; //1

	if (Left < Right) { //1
		Center = (Left + Right) / 2; //4
		Resource_logTime(5);
		MSort(A, TmpArray, Left, Center);
		MSort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
	Resource_logTime(4);
	Resource_logSpace(-SPACE);
}

void mergesort(ElementType A[], int N) {
    Resource_logSpace(SPACE_ELEMENT_INT);

	ElementType *TmpArray; //1
	TmpArray = malloc(N * sizeof(ElementType));
	Resource_logSpace(N * sizeof(ElementType));
	if (TmpArray != NULL) { //1
		MSort(A, TmpArray, 0, N - 1);
		free(TmpArray); //1
		Resource_logTime(1);
		Resource_logSpace(-N*sizeof(ElementType));
	} else
		fatalError( "No space for tmp array!!!" );
    Resource_logTime(4);
    Resource_logSpace(-SPACE_ELEMENT_INT);
}
/* END */

/* START: fig7_13.txt */
/* Return median of Left, Center, and Right */
/* Order these and hide the pivot */

ElementType Median3(ElementType A[], int Left, int Right) {
	const int SPACE = sizeof(ElementType) + 2*sizeof(int);
	Resource_logSpace(SPACE);

	int Center = (Left + Right) / 2; //3

	if (A[Left] > A[Center]){ //3
		Swap(&A[Left], &A[Center]); //4
		Resource_logTime(4);
	}
	if (A[Left] > A[Right]){ //3
		Swap(&A[Left], &A[Right]); //4
		Resource_logTime(4);
	}
	if (A[Center] > A[Right]){ //3
		Swap(&A[Center], &A[Right]); //4
		Resource_logTime(4);
	}
	/* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */

	Swap(&A[Center], &A[Right - 1]); /* Hide pivot */ //5

    Resource_logTime(19);
	Resource_logSpace(-SPACE);
	return A[Right - 1]; /* Return pivot */
}
/* END */

/* START: fig7_14.txt */
#define Cutoff ( 3 )

void Qsort(ElementType A[], int Left, int Right) {
	const int SPACE = sizeof(ElementType) + 2*sizeof(int);
	Resource_logSpace(SPACE);

	int i, j; //2
	ElementType Pivot; //1

	if (Left + Cutoff <= Right) { //2
		Pivot = Median3(A, Left, Right); //1

		i = Left; //1
		j = Right - 1; //2

		for (;;) {
			while (A[++i] < Pivot) { //4
			    Resource_logTime(4);
			}

			while (A[--j] > Pivot) {
			    Resource_logTime(4);
			}
			if (i < j){ //1
				Swap(&A[i], &A[j]); //4
				Resource_logTime(5);
			}
			else{
				Resource_logTime(1);
				break;
			}
		}
		Swap(&A[i], &A[Right - 1]); /* Restore pivot */ //5

		Qsort(A, Left, i - 1); //1
		Qsort(A, i + 1, Right); //1
		Resource_logTime(11);
	} else{
		/* Do an insertion sort on the subarray */
		insertionSort(A + Left, Right - Left + 1); // 3
		Resource_logTime(3);
	}
	Resource_logTime(7);
    Resource_logSpace(-SPACE);
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
	Resource_logSpace(SPACE_ELEMENT_INT);
	Qsort(A, 0, N - 1);
    Resource_logSpace(-SPACE_ELEMENT_INT);
}
/* END */

/* START: fig7_16.txt */
/* Places the kth smallest element in the kth position */
/* Because arrays start at 0, this will be index k-1 */
void Qselect(ElementType A[], int k, int Left, int Right) {
	const int SPACE = sizeof(ElementType) + 3*sizeof(int);
	Resource_logSpace(SPACE);

	int i, j; //2
	ElementType Pivot; //2

	if (Left + Cutoff <= Right) { //2
		Pivot = Median3(A, Left, Right); //1

		i = Left; //1
		j = Right - 1; //2
		for (;;) {
			while (A[++i] < Pivot) {
			}
			while (A[--j] > Pivot) {
			}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]); /* Restore pivot */

		if (k <= i)
			Qselect(A, k, Left, i - 1);
		else if (k > i + 1)
			Qselect(A, k, i + 1, Right);
	} else
		/* Do an insertion sort on the subarray */
		insertionSort(A + Left, Right - Left + 1);

	Resource_logSpace(-SPACE);
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

#define MaxSize 30000
int Arr1[MaxSize];
int Arr2[MaxSize];
int arr3[MaxSize];

void Sort_test() {
    int START=10;
    int END=1000;
    int STEP=10;
	int i;

	// test radix exchange sort
	//	printf("test radix exchange sort\n");
	//	int array[10] = { 10, 111, 110, 101, 111, 11, 110, 101, 0, 111 };
	//	printArray(array,10);
	//	radixExchangeSort(array, 2, 0, 9);


    Resource_initilizeOperationArray();

	Permute(Arr2, MaxSize);
    Resource_startTrack("sort","insertion-sort");
	for(i=START;i<=END;i+=STEP){
        Copy(Arr1, Arr2, i);
        Resource_clearData();
        insertionSort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();

	Resource_startTrack("sort","insertion-sort-best-case");
	for(i=START;i<=END;i+=STEP){
        Resource_clearData();
        insertionSort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();

	Resource_startTrack("sort","insertion-sort-worst-case");
	for(i=START;i<=END;i+=STEP){
	    reverseCopy(arr3, Arr1, i);
        Resource_clearData();
        insertionSort(arr3, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();


    START=200;
    END=MaxSize;
    STEP=200;

    Resource_startTrack("sort","heap-sort");
	for(i=START;i<=END;i+=STEP){
        Copy(Arr1, Arr2, i);
        Resource_clearData();
        heapsort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();

    Resource_startTrack("sort","merge-sort");
	for(i=START;i<=END;i+=STEP){
        Copy(Arr1, Arr2, i);
        Resource_clearData();
        mergesort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();

    Resource_startTrack("sort","quick-sort");
	for(i=START;i<=END;i+=STEP){
        Copy(Arr1, Arr2, i);
        Resource_clearData();
        quicksort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();

//    Resource_setMode(1);
    Resource_startTrack("sort","shell-sort");
	for(i=START;i<=END;i+=STEP){
        Copy(Arr1, Arr2, i);
        Resource_clearData();
        shellsort(Arr1, i);
        Resource_storeData(i);
	}
	Resource_analyseSequence();
    Resource_setMode(0);


   // --------------Time------------------
    char* list0[] = {"insertion-sort","insertion-sort-worst-case"};
    Resource_writePlotScript("quadratic",list0,2,0);

    char* list1[] = {"insertion-sort-best-case"};
    Resource_writePlotScript("insertion-best", list1,1,0);

    char* time2[] = {"shell-sort"};
    Resource_writePlotScript("shell-sort", time2, 1, 0);


    //---------------space----------------
    char* list2[] = {"insertion-sort","heap-sort","shell-sort"};
    Resource_writePlotScript("constant",list2,3,1);

    char* space1[] = {"quick-sort"};
    Resource_writePlotScript("quick-sort", space1,1,1);

    char* space2[] = {"merge-sort"};
    Resource_writePlotScript("merge-sort", space2,1,1);


    Resource_writeTableData("Sort");

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

