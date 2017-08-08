#pragma once
#include "alg_common.h"
ALG_NAMESPACE_BEG

typedef int ElemType;

/**
 *	单链队列
 */
struct QLNode
{
    ElemType        data;
    struct QLNode   *next;
};

struct QLSentinel
{
    struct QLNode   *front;
    struct QLNode   *tail;
};
Status InitQueue(QLSentinel *sentinel);
Status DestroyQueue(QLSentinel *sentinel);
Status EnQueue(QLSentinel *sentinel, ElemType e);
Status DeQueue(QLSentinel *sentinel, ElemType &e);

/**
 *	循环队列
 */
#define MAXQSIZE    100
struct CircleQueue
{
    ElemType    *base;
    int         front;
    int         tail;
};
Status InitQueue(CircleQueue &Q);
int QueueLength(CircleQueue Q);
Status EnQueue(CircleQueue &Q, ElemType e);
Status DeQueue(CircleQueue &Q, ElemType &e);

ALG_NAMESPACE_END

