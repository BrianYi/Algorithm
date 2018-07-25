#include "pubDef.h"
//////////////////////////////////////////////////////////////////////////
//
// 栈的顺序存储结构,顺序栈
// 
//////////////////////////////////////////////////////////////////////////

// 初始化
void init_seqstack( SeqStack &S )
{
	S.top = -1;
}

// 判栈空
bool is_empty_seqstack( SeqStack &S )
{
	if ( S.top == -1 )
		return true;
	else
		return false;
}

// 进栈
bool push_seqstack( SeqStack &S, int x )
{
	if ( S.top == MaxSize - 1 )
		return false;
	S.data[++S.top] = x;
	return true;
}

// 出栈
bool pop_seqstack( SeqStack &S, int x )
{
	if ( S.top == -1 )
		return false;
	x = S.data[S.top--];
	return true;
}

// 读栈顶元素
bool top_seqstack( SeqStack &S, int &x )
{
	if ( S.top == -1 )
		return false;
	x = S.data[S.top];
	return true;
}

// P64 4.设单链表的表头指针为L,结点结构由data和next两个域构成,其中data域为字符型。试设计算法判断该链表的全部n个字符是否中心对称。
// 例如xyx,xyyx都是中心对称。
bool is_symmetry_list( LinkList L, int n )
{
	int i;
	char *s = ( char* ) malloc( sizeof( char ) * ( n / 2 ) );
	LNode *p = L->next;
	for ( i = 0; i < n / 2; i++ )
	{
		s[i] = p->data;
		p = p->next;
	}
	i--;
	if ( n % 2 == 1 )
		p = p->next;
	while ( p&&s[i] == p->data )
	{
		i--;
		p = p->next;
	}
	if ( i == -1 )
		return true;
	else
		return false;
}

// P64 5.设有两个栈s1,s2都采用顺序栈方式,并且共享一个存储区[0,...,maxsize-1],为了尽量利用空间,减少溢出的可能,
// 可采用栈顶相向,迎面增长的存储方式。试设计s1,s2有关入栈和出栈的操作算法。
#define  MaxSize 100
typedef struct
{
	int data[MaxSize];
	int top[2];
}SeqStack;

bool push_seqstack(SeqStack &S, int i, int x )
{
	if ( i < 0 || i > 1 )
	{
		printf( "栈号输入错误!\n" );
		return false;
	}
	if ( S.top[1] - S.top[0] == 1 )
	{
		printf( "栈已满!\n" );
		return false;
	}
	if ( i == 0 )
		S.data[++S.top[0]] = x;
	else
		S.data[--S.top[1]] = x;
	return true;
}

int pop_seqstack( SeqStack &S, int i )
{
	if ( i < 0 || i > 1 )
	{
		printf( "栈号输入错误!\n" );
		return -1;
	}
	if ( S.top[0] == -1 || S.top[1] == MaxSize )
	{
		printf( "栈空!\n" );
		return -1;
	}
	if ( i == 0 )
		return S.data[S.top[0]--];
	else
		return S.data[S.top[1]++];
}