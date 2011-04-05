#include "avltree.h"
#include "testavl.h"
#include "resourcetrack.h"

#include <stdio.h>

void AVLTree_testPerformance(){
    int START=10;
    int END=1000;
    int STEP=10;

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
}


AVLTree_test()
{
    AvlTree T;
    Position P;
    int i;
    int j = 0;

    T = AVLTree_makeEmpty( NULL );
    for( i = 0; i < 50; i++, j = ( j + 7 ) % 50 )
        T = AVLTree_insert( j, T );
    for( i = 0; i < 50; i++ )
        if( ( P = AVLTree_find( i, T ) ) == NULL || AVLTree_retrieve( P ) != i )
            printf( "Error at %d\n", i );

 /* for( i = 0; i < 50; i += 2 )
        T = AVLTree_delete( i, T );

    for( i = 1; i < 50; i += 2 )
        if( ( P = AVLTree_find( i, T ) ) == NULL || AVLTree_retrieve( P ) != i )
            printf( "error at %d\n", i );
    for( i = 0; i < 50; i += 2 )
        if( ( P = AVLTree_find( i, T ) ) != NULL )
            printf( "error at %d\n", i );
*/
    printf( "Min is %d, Max is %d\n", AVLTree_retrieve( AVLTree_findMin( T ) ),
               AVLTree_retrieve( AVLTree_findMax( T ) ) );

    return 0;
}
