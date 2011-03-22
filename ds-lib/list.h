typedef int ElementType;

/* START: fig3_6.txt */
#ifndef _List_H
#define _List_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List List_makeEmpty(List L);
int List_isEmpty(List L);
int List_isLast(Position P, List L);
Position List_find(ElementType X, List L);
void List_delete(ElementType X, List L);
Position List_findPrevious(ElementType X, List L);
void List_insert(ElementType X, List L, Position P);
void List_deleteList(List L);
Position List_header(List L);
Position List_first(List L);
Position List_advance(Position P);
ElementType List_retrieve(Position P);

#endif    /* _List_H */
/* END */
