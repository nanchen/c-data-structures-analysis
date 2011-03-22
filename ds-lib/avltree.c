        #include "avltree.h"
        #include <stdlib.h>
        #include "fatal.h"

        struct AvlNode
        {
            ElementType Element;
            AvlTree  Left;
            AvlTree  Right;
            int      Height;
        };

        AvlTree
        AVLTree_makeEmpty( AvlTree T )
        {
            if( T != NULL )
            {
                AVLTree_makeEmpty( T->Left );
                AVLTree_makeEmpty( T->Right );
                free( T );
            }
            return NULL;
        }

        Position
        AVLTree_find( ElementType X, AvlTree T )
        {
            if( T == NULL )
                return NULL;
            if( X < T->Element )
                return AVLTree_find( X, T->Left );
            else
            if( X > T->Element )
                return AVLTree_find( X, T->Right );
            else
                return T;
        }

        Position
        AVLTree_findMin( AvlTree T )
        {
            if( T == NULL )
                return NULL;
            else
            if( T->Left == NULL )
                return T;
            else
                return AVLTree_findMin( T->Left );
        }

        Position
        AVLTree_findMax( AvlTree T )
        {
            if( T != NULL )
                while( T->Right != NULL )
                    T = T->Right;

            return T;
        }

/* START: fig4_36.txt */
        static int
        Height( Position P )
        {
            if( P == NULL )
                return -1;
            else
                return P->Height;
        }
/* END */

        static int
        Max( int Lhs, int Rhs )
        {
            return Lhs > Rhs ? Lhs : Rhs;
        }

/* START: fig4_39.txt */
        /* This function can be called only if K2 has a left child */
        /* Perform a rotate between a node (K2) and its left child */
        /* Update heights, then return new root */

        static Position
        SingleRotateWithLeft( Position K2 )
        {
            Position K1;

            K1 = K2->Left;
            K2->Left = K1->Right;
            K1->Right = K2;

            K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
            K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

            return K1;  /* New root */
        }
/* END */

        /* This function can be called only if K1 has a right child */
        /* Perform a rotate between a node (K1) and its right child */
        /* Update heights, then return new root */

        static Position
        SingleRotateWithRight( Position K1 )
        {
            Position K2;

            K2 = K1->Right;
            K1->Right = K2->Left;
            K2->Left = K1;

            K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
            K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

            return K2;  /* New root */
        }

/* START: fig4_41.txt */
        /* This function can be called only if K3 has a left */
        /* child and K3's left child has a right child */
        /* Do the left-right double rotation */
        /* Update heights, then return new root */

        static Position
        DoubleRotateWithLeft( Position K3 )
        {
            /* Rotate between K1 and K2 */
            K3->Left = SingleRotateWithRight( K3->Left );

            /* Rotate between K3 and K2 */
            return SingleRotateWithLeft( K3 );
        }
/* END */

        /* This function can be called only if K1 has a right */
        /* child and K1's right child has a left child */
        /* Do the right-left double rotation */
        /* Update heights, then return new root */

        static Position
        DoubleRotateWithRight( Position K1 )
        {
            /* Rotate between K3 and K2 */
            K1->Right = SingleRotateWithLeft( K1->Right );

            /* Rotate between K1 and K2 */
            return SingleRotateWithRight( K1 );
        }


/* START: fig4_37.txt */
        AvlTree
        AVLTree_insert( ElementType X, AvlTree T )
        {
            if( T == NULL )
            {
                /* Create and return a one-node tree */
                T = malloc( sizeof( struct AvlNode ) );
                if( T == NULL )
                    fatalError( "Out of space!!!" );
                else
                {
                    T->Element = X; T->Height = 0;
                    T->Left = T->Right = NULL;
                }
            }
            else
            if( X < T->Element )
            {
                T->Left = AVLTree_insert( X, T->Left );
                if( Height( T->Left ) - Height( T->Right ) == 2 )
                    if( X < T->Left->Element )
                        T = SingleRotateWithLeft( T );
                    else
                        T = DoubleRotateWithLeft( T );
            }
            else
            if( X > T->Element )
            {
                T->Right = AVLTree_insert( X, T->Right );
                if( Height( T->Right ) - Height( T->Left ) == 2 )
                    if( X > T->Right->Element )
                        T = SingleRotateWithRight( T );
                    else
                        T = DoubleRotateWithRight( T );
            }
            /* Else X is in the tree already; we'll do nothing */

            T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
            return T;
        }
/* END */

        AvlTree
        AVLTree_delete( ElementType X, AvlTree T )
        {
            printf( "Sorry; Delete is unimplemented; %d remains\n", X );
            return T;
        }

        ElementType
        AVLTree_retrieve( Position P )
        {
            return P->Element;
        }
