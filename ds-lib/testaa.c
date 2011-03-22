#include "aatree.h"
#include <stdio.h>

#define NumItems 20

int AATree_Test(void){
    AATree T;
    Position P;
    int i;
    int j = 0;

    T = AATree_Initialize( );
    T = AATree_MakeEmpty( NullNode );
    for( i = 0; i < NumItems; i++, j = ( j + 7 ) % NumItems )
        T = AATree_Insert( j, T );
    for( i = 0; i < NumItems; i++ )
        if( ( P = AATree_Find( i, T ) ) == NullNode || AATree_Retrieve( P ) != i )
            printf( "Error at %d\n", i );

    for( i = 0; i < NumItems; i += 2 )
        T = AATree_Remove( i, T );

    for( i = 1; i < NumItems; i += 2 )
        if( ( P = AATree_Find( i, T ) ) == NullNode || AATree_Retrieve( P ) != i )
            printf( "Error at %d\n", i );

    for( i = 0; i < NumItems; i += 2 )
        if( ( P = AATree_Find( i, T ) ) != NullNode )
            printf( "Error at %d\n", i );

    printf( "Min is %d, Max is %d\n", AATree_Retrieve( AATree_FindMin( T ) ),
               AATree_Retrieve( AATree_FindMax( T ) ) );

    return 0;
}
