#pragma once
#include "alg_common.h"
ALG_NAMESPACE_BEG

typedef int SElemType;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
/**
 *	À≥–Ú’ª
 */
struct SqStack
{
    SElemType   *base;
    SElemType   *top;
    int         stacksize;
};
Status InitStack(SqStack &S);
Status GetTop(SqStack S, SElemType &e);
Status Push(SqStack &S, SElemType e);
Status Pop(SqStack &S, SElemType &e);
void move(char a, char b);
void hanoi(int n, char x, char y, char z);


ALG_NAMESPACE_END


