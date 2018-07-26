#pragma once
#include "alg_common.h"
ALG_NAMESPACE_BEG

#define MAX_TREE_SIZE   100
typedef int ElemType;

typedef struct BiTNode
{
    ElemType        data;
    struct BiTNode  *lchild, *rchild;
}BiTNode, *BiTree;

Status CreateBiTree(BiTree &T);
Status PreOrderTraverse(BiTree T, Status(*Visit)(ElemType e));
Status InOrderTraverse(BiTree T, Status(*Visit)(ElemType e));
Status PostOrderTraverse(BiTree T, Status(*Visit)(ElemType e));
Status LevelOrderTraverse(BiTree T, Status(*Visit)(ElemType e));

ALG_NAMESPACE_END