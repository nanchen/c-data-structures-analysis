#include <stdio.h>
#include "queue.h"

int Queue_Test(void)
{
    Queue Q;
    int i;

    Q = Queue_CreateQueue( 12 );

    for( i = 0; i < 10; i++ )
        Queue_Enqueue( i, Q );

    while( !Queue_IsEmpty( Q ) )
    {
        printf( "%d\n", Queue_Front( Q ) );
        Queue_Dequeue( Q );
    }
    for( i = 0; i < 10; i++ )
        Queue_Enqueue( i, Q );

    while( !Queue_IsEmpty( Q ) )
    {
        printf( "%d\n", Queue_Front( Q ) );
        Queue_Dequeue( Q );
    }

    Queue_DisposeQueue( Q );
    return 0;
}
