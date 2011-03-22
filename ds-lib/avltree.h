        typedef int ElementType;

/* START: fig4_35.txt */
        #ifndef _AvlTree_H
        #define _AvlTree_H

        struct AvlNode;
        typedef struct AvlNode *Position;
        typedef struct AvlNode *AvlTree;

        AvlTree AVLTree_makeEmpty( AvlTree T );
        Position AVLTree_find( ElementType X, AvlTree T );
        Position AVLTree_findMin( AvlTree T );
        Position AVLTree_findMax( AvlTree T );
        AvlTree AVLTree_insert( ElementType X, AvlTree T );
        AvlTree AVLTree_delete( ElementType X, AvlTree T );
        ElementType AVLTree_retrieve( Position P );

        #endif  /* _AvlTree_H */
/* END */
