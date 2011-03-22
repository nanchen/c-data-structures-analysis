#include "avltree.h"
#include <stdio.h>

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
