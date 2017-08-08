#include "Queue.h"
ALG_NAMESPACE_BEG

Status InitQueue(QLSentinel *sentinel)
{
    sentinel->front = sentinel->tail = nullptr;
    return OK;
}

Status DestroyQueue(QLSentinel *sentinel)
{
    while (sentinel->front)
    {
        struct QLNode *q = sentinel->front;
        sentinel->front = q->next;
        free(q);
    }
    return OK;
}

Status EnQueue(QLSentinel *sentinel, ElemType e)
{
    struct QLNode *p = (QLNode *)malloc(sizeof(QLNode));
    if (!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = nullptr;
    sentinel->tail->next = p;
    sentinel->tail = p;
    return OK;
}

Status DeQueue(QLSentinel *sentinel, ElemType &e)
{
    if (sentinel->front == sentinel->tail)
        return ERROR;
    struct QLNode *q = sentinel->front;
    e = q->data;
    sentinel->front = q->next;
    if (sentinel->tail == q)
        sentinel->tail = sentinel->front;
    free(q);
    return OK;
}

Status InitQueue(CircleQueue &Q)
{
    Q.base = (ElemType *)malloc(MAXQSIZE * sizeof(ElemType));
    if (!Q.base)
        exit(OVERFLOW);
    Q.front = Q.tail = 0;
    return OK;
}

int QueueLength(CircleQueue Q)
{
    return (Q.tail - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(CircleQueue &Q, ElemType e)
{
    if ((Q.tail + 1) % MAXQSIZE == Q.front)
        return ERROR;
    Q.base[Q.tail] = e;
    Q.tail = (Q.tail + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(CircleQueue &Q, ElemType &e)
{
    if (Q.front == Q.tail)
        return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

ALG_NAMESPACE_END