typedef void* ElementType;

#ifndef _Queue_h
#define _Queue_h

struct QueueRecord;
typedef struct QueueRecord *Queue;

int Queue_IsEmpty(Queue Q);
int Queue_IsFull(Queue Q);
Queue Queue_CreateQueue(int MaxElements);
void Queue_DisposeQueue(Queue Q);
void Queue_MakeEmpty(Queue Q);
void Queue_Enqueue(ElementType X, Queue Q);
ElementType Queue_Front(Queue Q);
void Queue_Dequeue(Queue Q);
ElementType Queue_FrontAndDequeue(Queue Q);

#endif  /* _Queue_h */
/* END */
