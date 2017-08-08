#include "List.h"
ALG_NAMESPACE_BEG

//-------------------------------
// 顺序表

Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize)
    {
        ElemType *newBase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newBase)
            exit(OVERFLOW);
        L.elem = newBase;
        L.listsize += LISTINCREMENT;
    }
    ElemType *q = &L.elem[i - 1];
    for (ElemType *p = &L.elem[L.length - 1]; p >= q; p--)
        *(p + 1) = *p;
    *q = e;
    ++L.length;
    return OK;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
        return ERROR;
    ElemType *p = &L.elem[i - 1];
    e = *p;
    ElemType *q = L.elem + L.length - 1;
    for (++p; p <= q; ++p)
        *(p - 1) = *p;
    --L.length;
    return OK;
}

int LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
    int i = 1;
    ElemType *p = L.elem;
    while (i <= L.length && compare(*p++, e))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
    ElemType *pa = La.elem;
    ElemType *pb = Lb.elem;
    ElemType *pc = Lc.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;
    pc = Lc.elem = (ElemType *)malloc(Lc.listsize * sizeof(ElemType));
    if (!Lc.elem)
        exit(OVERFLOW);
    ElemType *pa_last = La.elem + La.length - 1;
    ElemType *pb_last = Lb.elem + Lb.length - 1;
    while (pa <= pa_last && pb <= pb_last)
    {
        if (*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }

    while (pa <= pa_last)
        *pc++ = *pa++;
    while (pb <= pb_last)
        *pc++ = *pb++;
}

//-------------------------------
// 单向链表
Status GetElem_L(struct LNode *L, int i, ElemType &e)
{
    struct LNode *p = L->next;
    int j = 1;
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    e = p->data;
    return OK;
}

Status ListInsert_L(struct LNode *L, int i, ElemType e)
{
    struct LNode *p = L;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i + 1)
        return ERROR;
    struct LNode *s = (struct LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status ListDelete_L(struct LNode *L, int i, ElemType &e)
{
    struct LNode *p = L;
    int j = 0;
    while (p->next && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    if (!p->next || j > i - 1)
        return ERROR;
    struct LNode *q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}

/**
 *	逆向建立链表
 */
void CreateList_L(struct LNode *L, int n)
{
    L = (struct LNode *)malloc(sizeof(LNode));
    L->next = nullptr;
    for (int i = n; i > 0; i--) 
    {
        struct LNode *p = (struct LNode *)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
}

void MergeList_L(struct LNode *La, struct LNode *Lb, struct LNode *Lc)
{
    struct LNode *pa = La->next;
    struct LNode *pb = Lb->next;
    struct LNode *pc = La;
    Lc = La;
    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(Lb);
}

void InitSpace_SL(SNode *space)
{
    for (int i = 0; i < MAXSIZE - 1; i++)
        space[i].next = 0;
}

int Malloc_SL(SNode *space)
{
    int i = space[0].next;
    if (space[0].next)
        space[0].next = space[i].next;
    return i;
}

void Free_SL(SNode *space, int k)
{
    space[k].next = space[0].next;
    space[0].next = k;
}

int LocateElem_SL(SNode *S, ElemType e)
{
    int i = S[0].next;
    while (i && S[i].data != e)
        i = S[i].next;
    return i;
}

DLNode* GetElemP_DL(struct DLNode *L, int i)
{
    struct DLNode *p = L->next;
    int j = 1;
    while (j != i && p)
    {
        p = p->next;
        j++;
    }
    if (j == i)
        return p;
    else
        return nullptr;
}

Status ListInsert_DL(struct DLNode *L, int i, ElemType e)
{
    struct DLNode *p = GetElemP_DL(L, i);
    if (!p)
        return ERROR;
    struct DLNode *s = (DLNode *)malloc(sizeof(DLNode));
    if (!s)
        return ERROR;
    s->data = e;
    s->pre = p->pre;
    p->pre->next = s;
    s->next = p;
    p->pre = s;
    return OK;
}

Status ListDelete_DL(struct DLNode *L, int i, ElemType &e)
{
    struct DLNode *p = GetElemP_DL(L, i);
    if (!p)
        return ERROR;
    e = p->data;
    p->pre->next = p->next;
    p->next->pre = p->pre;
    free(p);
    return OK;
}
ALG_NAMESPACE_END