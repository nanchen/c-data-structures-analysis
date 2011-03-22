        #include "list.h"
        #include <stdlib.h>
        #include "fatal.h"

        /* Place in the interface file */
        struct Node
        {
            ElementType Element;
            Position    Next;
        };

        List
        List_makeEmpty( List L )
        {
            if( L != NULL )
                List_deleteList( L );
            L = malloc( sizeof( struct Node ) );
            if( L == NULL )
                fatalError( "Out of memory!" );
            L->Next = NULL;
            return L;
        }

/* START: fig3_8.txt */
        /* Return true if L is empty */

        int
        List_isEmpty( List L )
        {
            return L->Next == NULL;
        }
/* END */

/* START: fig3_9.txt */
        /* Return true if P is the last position in list L */
        /* Parameter L is unused in this implementation */

        int List_isLast( Position P, List L )
        {
            return P->Next == NULL;
        }
/* END */

/* START: fig3_10.txt */
        /* Return Position of X in L; NULL if not found */

        Position
        List_find( ElementType X, List L )
        {
            Position P;

/* 1*/      P = L->Next;
/* 2*/      while( P != NULL && P->Element != X )
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_11.txt */
        /* List_delete from a list */
        /* Cell pointed to by P->Next is wiped out */
        /* Assume that the position is legal */
        /* Assume use of a header node */

        void
        List_delete( ElementType X, List L )
        {
            Position P, TmpCell;

            P = List_findPrevious( X, L );

            if( !List_isLast( P, L ) )  /* Assumption of header use */
            {                      /* X is found; delete it */
                TmpCell = P->Next;
                P->Next = TmpCell->Next;  /* Bypass deleted cell */
                free( TmpCell );
            }
        }
/* END */

/* START: fig3_12.txt */
        /* If X is not found, then Next field of returned value is NULL */
        /* Assumes a header */

        Position
        List_findPrevious( ElementType X, List L )
        {
            Position P;

/* 1*/      P = L;
/* 2*/      while( P->Next != NULL && P->Next->Element != X )
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_13.txt */
        /* List_insert (after legal position P) */
        /* List_header implementation assumed */
        /* Parameter L is unused in this implementation */

        void
        List_insert( ElementType X, List L, Position P )
        {
            Position TmpCell;

/* 1*/      TmpCell = malloc( sizeof( struct Node ) );
/* 2*/      if( TmpCell == NULL )
/* 3*/          fatalError( "Out of space!!!" );

/* 4*/      TmpCell->Element = X;
/* 5*/      TmpCell->Next = P->Next;
/* 6*/      P->Next = TmpCell;
        }
/* END */

#if 0
/* START: fig3_14.txt */
        /* Incorrect List_deleteList algorithm */

        void
        List_deleteList( List L )
        {
            Position P;

/* 1*/      P = L->Next;  /* List_header assumed */
/* 2*/      L->Next = NULL;
/* 3*/      while( P != NULL )
            {
/* 4*/          free( P );
/* 5*/          P = P->Next;
            }
        }
/* END */
#endif

/* START: fig3_15.txt */
        /* Correct List_deleteList algorithm */

        void
        List_deleteList( List L )
        {
            Position P, Tmp;

/* 1*/      P = L->Next;  /* List_header assumed */
/* 2*/      L->Next = NULL;
/* 3*/      while( P != NULL )
            {
/* 4*/          Tmp = P->Next;
/* 5*/          free( P );
/* 6*/          P = Tmp;
            }
        }
/* END */

        Position
        List_header( List L )
        {
            return L;
        }

        Position
        List_first( List L )
        {
            return L->Next;
        }

        Position
        List_advance( Position P )
        {
            return P->Next;
        }

        ElementType
        List_retrieve( Position P )
        {
            return P->Element;
        }
