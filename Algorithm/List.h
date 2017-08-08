#pragma once
#include "alg_common.h"
ALG_NAMESPACE_BEG

#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10

typedef int ElemType;

/**
 *	顺序表
 */
struct SqList
{
    ElemType    *elem;
    int         length;
    int         listsize;
};
Status InitList_Sq(SqList &L);
Status ListInsert_Sq(SqList &L, int i, ElemType e);
Status ListDelete_Sq(SqList &L, int i, ElemType &e);
int LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType));
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc);

/**
 *	单向链表
 */
struct LNode
{
    ElemType        data;
    struct LNode    *next;
};
Status GetElem_L(struct LNode *L, int i, ElemType &e);
Status ListInsert_L(struct LNode *L, int i, ElemType e);
Status ListDelete_L(struct LNode *L, int i, ElemType &e);
void CreateList_L(struct LNode *L, int n);
void MergeList_L(struct LNode *La, struct LNode *Lb, struct LNode *Lc);

/**
 *	静态链表
 */
#define MAXSIZE 1000
struct SNode
{
    ElemType    data;
    int         next;
};
void InitSpace_SL(SNode *space);
int Malloc_SL(SNode *space);
void Free_SL(SNode *space, int k);
int LocateElem_SL(SNode *S, ElemType e);

/**
 *	双向链表
 */
struct DLNode
{
    ElemType        data;
    struct DLNode   *pre;
    struct DLNode   *next;
};
DLNode* GetElemP_DL(struct DLNode *L, int i);
Status ListInsert_DL(struct DLNode *L, int i, ElemType e);
Status ListDelete_DL(struct DLNode *L, int i, ElemType &e);

ALG_NAMESPACE_END