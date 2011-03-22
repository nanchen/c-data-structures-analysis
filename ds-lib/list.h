typedef int ElementType;

/* START: fig3_6.txt */
#ifndef _List_H
#define _List_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List List_MakeEmpty(List L);
int List_IsEmpty(List L);
int List_IsLast(Position P, List L);
Position List_Find(ElementType X, List L);
void List_Delete(ElementType X, List L);
Position List_FindPrevious(ElementType X, List L);
void List_Insert(ElementType X, List L, Position P);
void List_DeleteList(List L);
Position List_Header(List L);
Position List_First(List L);
Position List_Advance(Position P);
ElementType List_Retrieve(Position P);

#endif    /* _List_H */
/* END */
