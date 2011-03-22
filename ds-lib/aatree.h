#include <stdlib.h>
#include "fatal.h"

typedef int ElementType;

#ifndef _AATree_H
#define _AATree_H

struct AANode;
typedef struct AANode *Position;
typedef struct AANode *AATree;

AATree AATree_MakeEmpty(AATree T);
Position AATree_Find(ElementType X, AATree T);
Position AATree_FindMin(AATree T);
Position AATree_FindMax(AATree T);
AATree AATree_Initialize(void);
AATree AATree_Insert(ElementType X, AATree T);
AATree AATree_Remove(ElementType X, AATree T);
ElementType AATree_Retrieve(Position P);

extern Position NullNode;

#endif  /* _AATree_H */

/* END */
