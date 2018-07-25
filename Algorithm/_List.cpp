#include "pubDef.h"
//////////////////////////////////////////////////////////////////////////
// 
// 线性表的链式表示
// 
//////////////////////////////////////////////////////////////////////////

// 头插法建立链表O(n)
LinkList head_insert_create_list( LinkList &L )
{
	LNode *s;
	int x;
	L = ( LinkList ) malloc( sizeof( LNode ) );
	L->next = NULL;
	scanf_s( "%d", &x );
	while ( x != -1 )
	{
		s = ( LNode * ) malloc( sizeof( LNode ) );
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf_s( "%d", &x );
	}
	return L;
}

// 尾插法建立链表O(n)
LinkList tail_insert_create_list( LinkList &L )
{
	int x;
	L = ( LinkList ) malloc( sizeof( LNode ) );
	LNode *s, *r = L;
	scanf_s( "%d", &x );
	while ( x != -1 )
	{
		s = ( LNode * ) malloc( sizeof( LNode ) );
		s->data = x;
		r->next = s;
		r = s;
		scanf_s( "%d", &x );
	}
	r->next = NULL;
	return L;
}

// 按序号查找结点值O(n)
LNode *get_elem_list( LinkList L, int i )
{
	int j = 1;
	LNode *p = L->next;
	if ( i == 0 )
		return L;
	if ( i < 1 )
		return NULL;
	while ( p&&j < i )
	{
		p = p->next;
		j++;
	}
	return p;
}

// 按值查找表结点O(n)
LNode *locate_elem_list( LinkList L, int val )
{
	LNode *p = L->next;
	while ( p&&p->data != val )
		p = p->next;
	return p;
}

// P37 1.设计一个递归算法,删除不带头结点的单链表L中所有值为x的结点。
// 注:不会断链,因为采用了引用
void del_x_no_head_list( LinkList &L, int x )
{
	LNode *&p = L, *q;
	if ( p == NULL )
		return;
	if ( p->data == x )
	{
		q = p;
		p = p->next;
		free( q );
		del_x_no_head_list( p, x );
	}
	else
		del_x_no_head_list( p->next, x );
}

// P37 2.在带头结点的单链表L中,删除所有值为x的结点,并释放其空间,假设值为x的结点不唯一,试编写算法以实现上述操作。
void del_x_list( LinkList &L, int x )
{
	LNode *p = L->next, *pre = L, *q;
	while ( p )
	{
		if ( p->data == x )
		{
			q = p;
			p = p->next;
			pre->next = p;
			free( q );
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

// P37 3.设L为带头结点的单链表,编写算法实现从尾到头反向输出每个结点的值。
void reverse_print_list( LinkList L )
{
	if ( L->next )
		reverse_print_list( L->next );
	printf( "%d", L->data );
}

// P37 4.试编写在带头结点的单链表L中删除一个最小值结点的高效算法(假设最小值结点是唯一的)。
LinkList del_min_list( LinkList &L )
{
	LNode *minp, *p, *minpre, *pre;
	minpre = pre = L;
	minp = p = L->next;
	while ( p )
	{
		if ( p->data < minp->data )
		{
			minp = p;
			minpre = pre;
		}
		pre = p;
		p = p->next;
	}
	minpre->next = minp->next;
	free( minp );
	return L;
}

// P37 5.试编写算法将带头结点的单链表就地逆置,所谓"就地"是指辅助空间复杂度为O(1)。
LinkList reverse_list( LinkList L )
{
	LNode *p, *r;
	p = L->next;
	L->next = NULL;
	while ( p )
	{
		r = p->next;
		p->next = L->next;
		L->next = p;
		p = r;
	}
	return L;
}

// P37 6.有一个带头结点的单链表L,设计一个算法使其元素递增有序
void sort_list( LinkList &L )
{
	LNode *p = L->next, *pre;
	LNode *r = p->next;
	p->next = NULL;
	p = r;
	while ( p )
	{
		r = p->next;
		pre = L;
		while ( pre->next&&pre->next->data < p->data )
			pre = pre->next;
		p->next = pre->next;
		pre->next = p;
		p = r;
	}
}

// P37 7.设在一个带表头结点的单链表中所有元素结点的数据值无序,试编写一个函数,删除表中所有介于给定的两个值(作为函数参数给出)之间的元素
// 的元素(若存在)。
void del_s2t_list( LinkList &L, int s, int t )
{
	LNode *pre = L, *p = L->next;
	while ( p )
	{
		if ( p->data > s && p->data < t )
		{
			pre->next = p->next;
			free( p );
			p = pre->next;
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

// P37 8.给定两个单链表,编写算法找出两个链表的公共结点。
LinkList search_common_list( LinkList L1, LinkList L2 )
{
	int len1 = Length( L1 ), len2 = Length( L2 );
	LinkList LL, SL;	// LL=long list, SL=short list
	if ( len1 > len2 )
	{
		LL = L1->next;
		SL = L2->next;
	}
	else
	{
		LL = L2->next;
		SL = L1->next;
	}
	int dist = abs( len1 - len2 );
	while ( dist-- )
		LL = LL->next;
	while ( LL )
	{
		if ( LL == SL )
			return LL;
		else
		{
			LL = LL->next;
			SL = SL->next;
		}
	}
	return NULL;
}

// P37 9.给定一个带表头结点的单链表,设head为头指针,结点的结构为(data,next),data为整型元素,next为指针,试写出算法:按递增次序输出单链表
// 中各结点的数据元素,并释放结点所占的存储空间(要求:不允许使用数组作为辅助空间)。
void del_min_until_empty_list( LinkList &head )
{
	LNode *p, *pre, *q;
	while ( head->next )
	{
		pre = head;
		p = pre->next;
		while ( p->next )
		{
			if ( p->next->data < pre->next->data )
				pre = p;
			p = p->next;
		}
		printf( "%d", pre->next->data );
		q = pre->next;
		pre->next = q->next;
		free( q );
	}
	free( head );
}

// P37 10.将一个带头结点的单链表A分解为两个带头结点的单链表A和B,使得A表中含有原表中序号为奇数的元素,而B表中含有原表中序号为偶数的元素,
// 且保持其相对顺序不变。
LinkList split_A_2_AB_list( LinkList &A )
{
	LinkList B = ( LinkList ) malloc( sizeof( LNode ) );
	LNode *rA = A, *rB = B;
	LNode *p = A->next;
	A->next = B->next = NULL;
	int i = 0;
	while ( p )
	{
		i++;
		if ( i % 2 )
		{
			rA->next = p;
			rA = p;
		}
		else
		{
			rB->next = p;
			rB = p;
		}
		p = p->next;
	}
	rA->next = NULL;
	rB->next = NULL;
	return B;
}

// P37 11.设C={a1,b1,a2,b2,...,an,bn}为线性表,采用带头结点的hc单链表存放,设计一个就地算法,将其拆分为两个线性表,使得
// A={a1,a2,...,an}, B={bn,...,b2,b1}
LinkList split_A_2_AB2_list( LinkList &A )
{
	LinkList B = ( LinkList ) malloc( sizeof( LNode ) );
	LNode *rA = A;
	LNode *p = A->next, *q;
	B->next = NULL;
	while ( p )
	{
		rA->next = p;	// 尾插法
		rA = p;
		p = p->next;

		q = p->next;	// 存储后继防断链

		p->next = B->next;	// 头插法
		B->next = p;
		p = q;
	}
	rA->next = NULL;
	return B;
}

// P37 12.在一个递增有序的线性表中,有数值相同的元素存在。若存储方式为单链表,设计算法去掉数值相同的元素,使表中不再有重复的元素。例如
// (7,10,10,21,30,42,42,42,51,70)将变作(7,10,21,30,42,51,70)。
void del_same_ordered_list( LinkList &L )
{
	LNode *p = L->next, *q;
	if ( !p )
		return;
	while ( p->next )
	{
		q = p->next;
		if ( p->data == q->data )
		{
			p->next = q->next;
			free( q );
		}
		else
			p = p->next;
	}
}
// P37 13.假设有两个按元素值递增次序排列的线性表,均以单链表形式存储。请编写算法将这两个单链表归并为一个按元素值递减次序排列的单链表,并
// 要求利用原来两个单链表的结点存放归并后的单链表。
void merge_ab2a_ordered_list( LinkList &LA, LinkList &LB )
{
	LNode *rA, *rB, *pA, *pB;
	pA = LA->next;
	pB = LB->next;
	LA->next = NULL;
	while ( pA&&pB )
	{
		if ( pA->data <= pB->data )
		{
			rA = pA->next;
			pA->next = LA->next;
			LA->next = pA;
			pA = rA;
		}
		else
		{
			rB = pB->next;
			pB->next = LA->next;
			LA->next = pB;
			pB = rB;
		}
	}
	if ( pA )
		pB = pA;
	while ( pB )
	{
		rB = pB->next;
		pB->next = LA->next;
		LA->next = pB;
		pB = rB;
	}
	free( LB );
}

// P37 14.设A和B是两个单链表(带头结点),其中元素递增有序。设计一个算法从A和B中公共元素产生单链表C,要求不破坏A,B的结点。
LinkList generate_common_ordered_list( LinkList A, LinkList B )
{
	LNode *p = A->next, *q = B->next, *r, *s;
	LinkList C = ( LinkList ) malloc( sizeof( LNode ) );
	r = C;
	while ( p&&q )
	{
		if ( p->data < q->data )
			p = p->next;
		else if ( p->data > q->data )
			q = q->next;
		else
		{
			s = ( LNode* ) malloc( sizeof( LNode ) );
			s->data = p->data;
			r->next = s;
			r = s;
			p = p->next;
			q = q->next;
		}
		r->next = NULL;
	}
	return C;
}

// P37 15.已知两个链表A和B分别表示两个集合,其元素递增排列。编制函数,求A与B的交集,并存放于A链表中。
LinkList intersection_ab2a_ordered_list( LinkList &LA, LinkList &LB )
{
	LNode *pA, *pB, *pC, *q;
	pA = LA->next;
	pB = LB->next;
	pC = LA;
	while ( pA&&pB )
	{
		if ( pA->data == pB->data )
		{
			pC->next = pA;
			pC = pA;
			pA = pA->next;
			q = pB;
			pB = pB->next;
			free( q );
		}
		else if ( pA->data < pB->data )
		{
			q = pA;
			pA = pA->next;
			free( q );
		}
		else
		{
			q = pB;
			pB = pB->next;
			free( q );
		}
	}
	while ( pA )
	{
		q = pA;
		pA = pA->next;
		free( q );
	}
	while ( pB )
	{
		q = pB;
		pB = pB->next;
		free( q );
	}
	pC->next = NULL;
	free( LB );
	return LA;
}

// P38 16.两个整数序列A=a1,a2,a3,...,am和B=b1,b2,b3,...,bn已经存入两个单链表中,设计一个算法,判断序列B是否是序列A的连续子序列。
bool is_subsequence_list( LinkList A, LinkList B )
{
	LNode *pA, *pB, *preA;
	pA = A;
	pB = B;
	preA = pA;
	while ( pA&&pB )
	{
		if ( pA->data == pB->data )
		{
			pA = pA->next;
			pB = pB->next;
		}
		else
		{
			preA = preA->next;
			pA = preA;
			pB = B;
		}
	}
	if ( !pB )
		return true;
	return false;
}

// P38 17.设计一个算法用于判断带头结点的循环双链表是否对称。
bool is_symmetry_dblist( DLinkList L )
{
	DNode *pA, *pB;
	pA = L->next;
	pB = L->prior;
	while ( pA != pB&&pA != pB->next )
	{
		if ( pA->data == pB->data )
		{
			pA = pA->next;
			pB = pB->prior;
		}
		else
			return false;
	}
	return true;
}

// P38 18.有两个循环单链表,链表头指针分别为LA和LB,编写一个函数将链表h2链接到链表h1之后,要求链接后的链表仍保持循环链表形式。
LinkList link_cycle_list( LinkList &LA, LinkList &LB )
{
	LNode *pA, *pB;
	pA = LA;
	pB = LB;
	while ( pA->next != LA )
		pA = pA->next;
	while ( pB->next != LB )
		pB = pB->next;
	pA->next = LB;
	pB->next = LA;
	return LA;
}

// P38 19.设有一个带头结点的循环单链表,其结点值均为正整数。设计一个算法,反复找出单链表中结点值最小的结点并输出,然后将该结点从中删除,直
// 到单链表空为止,再删除表头结点。
void del_minimum_until_empty_list( LinkList &L )
{
	LNode *p, *pre, *minp, *minpre;
	while ( L->next != L )
	{
		minp = p = L->next;
		minpre = pre = L;
		while ( p != L )
		{
			if ( p->data < minp->data )
			{
				minp = p;
				minpre = pre;
			}
			pre = p;
			p = p->next;
		}
		printf( "%d", minp->data );
		minpre->next = minp->next;
		free( minp );
	}
	free( L );
}

// P38 20.设头指针为L的带有表头结点的非循环双向链表,其每个结点中除有prior(前驱指针),data(数据)和next(后继指针)域外,还有一个访问频度
// 域freq。在链表被启用前,其值均初始化为零。每当在链表中进行一次Locate(L,x)运算时,令元素值为x的结点中freq域的值增1,并使此链表中结点保
// 持按访问频度非增(递减)的顺序排列,同时最近访问的结点排在频度相同的结点的前面,以便使频繁访问的结点总是靠近表头。试编写符合上述要求的
// Locate(L,x)运算的算法,该运算为函数过程,返回找到结点的地址,类型为指针。
DLinkList update_MRU_dlist( DLinkList &L, int x )
{
	DNode *p, *pre;
	p = L->next;
	pre = L;
	while ( p&&p->data != x )
		p = p->next;
	if ( !p )
	{
		printf( "不存在值为%d的结点", x );
		return NULL;
	}
	else
	{
		p->freq++;
		p->next->prior = p->prior;
		p->prior->next = p->next;
		pre = p->prior;
		while ( pre != L&&pre->freq <= p->freq )
			pre = pre->prior;
		p->next = pre->next;
		pre->next->prior = p;
		p->prior = pre;
		pre->next = p;
	}
	return p;
}

// P38 21.已知一个带有表头结点的单链表,结点结构为[data|link],假设该链表只给出了头指针list。在不改变链表的前提下,请设计一个尽可能高效
// 的算法,查找链表中倒数第k个位置上的结点(k为正整数)。若查找成功,算法输出该结点的data域的值,并返回1;否则,只返回0。要求:
// 1)描述算法的基本设计思想。
// 2)描述算法的详细实现步骤。
// 3)根据设计思想和实现步骤,采用程序设计语言描述算法(使用C,C++或Java语言实现关键之处请给出简要注释)
typedef struct LNode
{
	int data;
	struct LNode *link;
}LNode, *LinkList;

bool search_k_reverse_list( LinkList L, int k )
{
	LNode *p, *q;
	q = p = L->link;
	int count = 0;
	while ( p )
	{
		if ( count < k )
			count++;
		else
			q = q->link;
		p = p->link;
	}
	if ( count < k )
		return false;
	else
	{
		printf( "%d", q->data );
		return true;
	}
}

// P38 22.假定采用带头结点的单链表保存单词,当两个单词有相同的后缀时,则可共享相同的后缀存储空间,例如,"loading"和"being"的存储映射如下
// 图所示。
// str1
//	\	
//	[|]->[l|]->[o|]->[a|]->[d|]--
//								 \
// str2							 [i|]->[n|]->[g|^]
//	\							 /
//	[|]->[b|]->[e|]--------------
// 设str1和str2分别指向两个单词所在单链表的头结点,链表结点结构为[data|next],请设计一个时间上尽可能高效的算法,找出由str1和str2所指向
// 两个链表共同后缀的起始位置(如图中字符i所在结点的位置p)。要求:
// 1)给出算法的基本设计思想。
// 2)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// 3)说明你所设计算法的时间复杂度和空间复杂度。
typedef struct LNode
{
	char data;
	struct LNode *next;
}LNode;

int Length( LNode *head )
{
	int len = 0;
	while ( head->next )
	{
		len++;
		head = head->next;
	}
	return len;
}

LNode *find_common( LNode *str1, LNode *str2 )
{
	int len1, len2;
	LNode *p, *q;
	len1 = Length( str1 );
	len2 = Length( str2 );
	for ( p = str1; len1 > len2; len1-- )
		p = p->next;
	for ( q = str2; len1 < len2; len2-- )
		q = q->next;
	while ( p->next&&p->next != q->next )
	{
		p = p->next;
		q = q->next;
	}
	return p->next;
}

// P38 23.用单链表保存m个整数,结点的结构为:[data|link],且|data|≤n(n为正整数)。现要求设计一个时间复杂度尽可能高效的算法,对于链表中
// data的绝对值相等的结点,仅保留第一次出现的结点而删除其余绝对值相等的结点。例如,若给定的单链表head如下:
// Head
//  \
//  [|]->[21|]->[15|]->[15|]->[-7|]->[15|^]
//  则删除结点后的head为:
// Head
//  \
//  [|]->[21|]->[15|]->[-7|]
// 要求:
// 1)给出算法的基本设计思想。
// 2)使用C或C++语言,给出单链表结点的数据类型定义。
// 3)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// 4)说明你所设计算法的时间复杂度和空间复杂度。
typedef struct LNode
{
	int data;
	struct LNode *link;
}LNode, *LinkList;

void del_abs_same_list( LinkList &L, int n )
{
	LNode *p, *q;
	p = L;
	int *s, m;
	s = ( int* ) malloc( sizeof( int )*( n + 1 ) );
	for ( int i = 0; i < n + 1; i++ )
		s[i] = 0;
	while ( p->link )
	{
		m = p->link->data > 0 ? p->link->data : -p->link->data;
		if ( s[m] == 0 )
		{
			s[m] = 1;
			p = p->link;
		}
		else
		{
			q = p->link;
			p->link = q->link;
			free( q );
		}
	}
	free( s );
}