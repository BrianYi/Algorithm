#pragma once
/*!
 * \file	GList.h
 *
 * \author	BrianYi
 * \date	2017/08/08
 *
 * \brief	广义表
 */
#include "alg_common.h"
ALG_NAMESPACE_BEG

typedef int ElemType;

enum ElemTag
{
    ATOM,
    LIST
};

struct AtomType
{
    ElemType    data;
};

struct ListType
{
    struct GLNode *head;
    struct GLNode *tail;
};
/**
 *	广义表-头尾链表存储表示
 */
struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType    atom;
        ListType    list;
    };
};


/**
 *	广义表-线性链表存储表示
 */

ALG_NAMESPACE_END
