#pragma once
/*!
 * \file	GList.h
 *
 * \author	BrianYi
 * \date	2017/08/08
 *
 * \brief	�����
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
 *	�����-ͷβ����洢��ʾ
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
 *	�����-��������洢��ʾ
 */

ALG_NAMESPACE_END
