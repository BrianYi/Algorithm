#include "Stack.h"
ALG_NAMESPACE_BEG

Status InitStack(SqStack &S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status Push(SqStack &S, SElemType e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

void move(char a, char b)
{
    printf("%c -> %c\n", a, b);
}

void hanoi(int n, char x, char y, char z)
{
    if (n == 1)
        move(x,z);
    else
    {
        hanoi(n - 1, x, z, y);
        move(x, z);
        hanoi(n - 1, y, x, z);
    }
}

ALG_NAMESPACE_END