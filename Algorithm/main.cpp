#include "pubDef.h"
//////////////////////////////////////////////////////////////////////////
//
// 线性表的顺序表示
// 
//////////////////////////////////////////////////////////////////////////

// 插入操作O(n)
bool insert_seq( SeqList &L, int i, int val )
{
	if ( i<1 || i >L.length + 1 )
		return false;
	if ( L.length >= L.maxSize )
		return false;
	for ( int j = L.length; j >= i; j-- )
		L.data[j] = L.data[j - 1];
	L.data[i - 1] = val;
	L.length++;
	return true;
}

// 删除操作O(n)
bool del_seq( SeqList &L, int i, int val )
{
	if ( i<1 || i>L.length )
		return false;
	val = L.data[i - 1];
	for ( int j = i; j < L.length; j++ )
		L.data[j - 1] = L.data[j];
	L.length--;
	return true;
}

// 按值查找O(n)
int locate_elem_seq( SeqList L, int val )
{
	for ( int i = 0; i < L.length; i++ )
		if ( L.data[i] == val )
			return i + 1;
	return 0;
}

// WP18 1.从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删除元素的值。空出的位置由最后一个元素填补,若顺序表为空则
// 显示出错信息并退出。
bool del_min_seq( SeqList &L, int &val )
{
	if ( L.length == 0 )
		return false;
	val = L.data[0];
	int pos = 0;
	for ( int i = 1; i < L.length; i++ )
	{
		if ( L.data[i] < val )
		{
			val = L.data[i];
			pos = i;
		}
	}
	L.data[pos] = L.data[L.length - 1];
	L.length--;
	return true;
}

// WP18 2.设计一个高效的算法,将顺序表的所有元素逆置,要求算法的空间复杂度为O(1)。
void reverse_seq( SeqList &L, int from, int to)
{
	if ( from >= to || to >= L.length )
		return;
	for ( int i = 0; i < ( to - from + 1 ) / 2; i++ )
		swap( L.data[from + i], L.data[to - i] );
}

// WP18 3.长度为n的顺序表L,编写一个时间复杂度为O(n),空间复杂度为O(1)的算法,该算法删除线性表中所有值为x的数据元素。
// 
// 解法:用k记录顺序表L中不等于x的元素个数(即需要保存的元素个数),边扫描L边统计k,并将不等于x的元素向前放置k位置上,最后修改L的长度。
void del_x_seq( SeqList &L, int x )
{
	int k = 0;
	for ( int i = 0; i < L.length; i++ )
	{
		if ( L.data[i] != x )
			L.data[k++] = L.data[i];
	}
	L.length = k;
}

// WP18 4.从有序顺序表中删除其值在给定值s与t之间(要求s<t)的所有元素,如果s或t不合理或者顺序表为空则显示出错信息并退出运行。
// 
// 算法思想:先寻找值大于等于s的第一个元素(第一个删除的元素),然后寻找值>t的第一个元素(最后一个删除的元素的下一个元素),
// 要将这段元素删除,则只需直接将后面的元素前移即可。
bool del_s2t_ordered_seq( SeqList &L, int s, int t )
{
	int i, j;
	if ( s >= t || L.length == 0 ) 
		return false;
	for ( i = 0; i < L.length&&L.data[i] < s; i++ );
	if ( i >= L.length ) 
		return false;
	for ( j = i; j < L.length&&L.data[j] <= t; j++ );
	for ( ; j < L.length; i++, j++ )
		L.data[i] = L.data[j];
	if ( i != j )
		L.length = i + 1;
	return true;
}

// WP18 5.从顺序表中删除其值在给定值s与t之间(包含s和t,要求s<t)的所有元素,如果s或t不合理或者顺序表为空则显示出错信息并退出运行。
// 
// 算法思想:从前向后扫描顺序表L,用k记录下元素值在s到t之间元素的个数(出世时k=0)。对于当前扫描的元素,若其值不在s到t之间,则前移k个位置;
// 否则执行k++。由于这样每个不在s到t之间的元素仅移动一次,所以算法效率高。
bool del_s2t_seq( SeqList &L, int s, int t )
{
	int k = 0;
	if ( L.length == 0 || s >= t )
		return false;
	for ( int i = 0; i < L.length; i++ )
	{
		if ( L.data[i]<s || L.data[i]>t )
			L.data[k++] = L.data[i];
	}
	L.length = k;
	return true;
}

// WP18 6.从有序顺序表中删除所有其值重复的元素,使表中所有元素的值均不同。
// 
// 算法思想:注意是有序顺序表,值相同的元素一定在连续的位置上,用类似于直接插入排序的思想,初始时将第一个元素看做非重复的有序表.
// 之后依次判断后面的元素是否与前面非重复有序表的最后一个元素相同,如果相同则继续向后判断,如果不同则插入到前面的非重复有序表的最后,
// 直至判断到表尾为止。
bool del_same_ordered_seq( SeqList &L )
{
	int k = 0;
	for ( int i = 0; i < L.length; i++ )
	{
		if ( L.data[k] != L.data[i] )
			L.data[++k] = L.data[i];
	}
	L.length = k + 1;
	return true;
}

// WP18 7.将两个有序顺序表合并成一个新的有序顺序表,并由函数返回结果顺序表。
// 
// 算法思想:首先,按顺序不断取下两个顺序表表头较小的结点存入新的顺序表中。然后,看哪个表还有剩余,将剩下的部分加到新的顺序表后面。
bool merge_ab2c_ordered_seq( SeqList A, SeqList B, SeqList &C )
{
	if ( A.length + B.length > C.maxSize )
		return false;
	int i = 0, j = 0, k = 0;
	while ( i < A.length &&j < B.length )
	{
		if ( A.data[i] <= B.data[j] )
			C.data[k++] = A.data[i++];
		else
			C.data[k++] = B.data[j++];
	}
	while ( i < A.length )
		C.data[k++] = A.data[i++];
	while ( j < B.length )
		C.data[k++] = B.data[j++];
	C.length = k + 1;
	return true;
}

// WP18 8.已知在一维数组A[m+n]中依次存放着两个线性表(a1,a2,a3,...,am)和(b1,b2,b3,...,bn)。试编写一个函数,将数组中两个顺序表的位
// 置互换,即将(b1,b2,b3,...,bn)放在(a1,a2,a3,...,am)的前面。
// 
// 算法思想:原地逆置,再对前n个元素,后m个元素分别使用逆置算法。
void exchange_seq( SeqList &A, int m, int n )
{
	reverse_seq( A, 0, m + n - 1 );
	reverse_seq( A, 0, n - 1 );
	reverse_seq( A, n, m + n - 1 );
}

// WP18 9.线性表(a1,a2,a3,...,an)中元素递增有序且按顺序存储于计算机内。要求设计一算法完成用最少时间在表中查找数值为x的元素,若找到
// 将其与后继元素位置相交换,若找不到将其插入表中并使表中元素仍递增有序。
// 
// 算法思想:顺序存储的线性表递增有序,可以顺序查找,也可以折半查找。题目要求"用最少的时间在表中查找数值为x的元素",这里使用折半查找法。
int binary_search_seq( SeqList &A, int x )
{
	int low = 0, high = A.length - 1, mid;
	while ( low <= high )
	{
		mid = ( low + high ) / 2;
		if ( A.data[mid] == x )	return mid;
		else if ( A.data[mid] < x ) low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}

void search_exchange_insert_ordered_seq( SeqList &A, int x )
{
	int low = 0, high = A.length - 1, mid;
	while ( low <= high )
	{
		mid = ( low + high ) / 2;
		if ( A.data[mid] == x ) break;	
		else if ( A.data[mid] < x ) low = mid + 1;
		else high = mid - 1;
	}
	if ( A.data[mid] == x&&mid != A.length - 1 )
		swap( A.data[mid], A.data[mid + 1] );
	if ( low > high )
	{
		int i;
		for ( i = A.length - 1; i > high; i-- )
			A.data[i + 1] = A.data[i];
		A.data[i + 1] = x;
		A.length += 1;
	}
}

// WP18 10.设将n(n>1)个整数存放到一维数组R中。试设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移p(0<p<n)个位 
// 置,即将R中的数据由(X0,X1,...,Xn-1)变换为(Xp,Xp+1,...,Xn-1,X0,X1,...,Xp-1)。要求:
// (1)给出算法的基本设计思想。
// (2)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。
// 
// 算法思想:ab=>ba,先逆置a,再逆置b,再两者都逆置
void shift_left_seq( SeqList& L, int p )
{
	reverse_seq( L, 0, p - 1 );
	reverse_seq( L, p, L.length - 1 );
	reverse_seq( L, 0, L.length - 1 );
}

// WP18 11.一个长度为L(L≥1)的升序序列S,处在⌈L/2⌉个位置的数称为S的中位数。例如,若序列S1=(11,13,15,17,19),则S1的中位数是15,两个
// 序列的中位数是含它们所有原色的升序序列的中位数。例如,S2=(2,4,6,8,20),则S1和S2的中位数是11。现在有两个等长升序序列A和B,试设计一
// 个在时间和空间两方面都尽可能高效的算法,找出两个序列A和B的中位数。要求:
// (1)给出算法的基本设计思想。
// (2)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。
// 
// 算法思想:
// 分别求两个升序序列A,B的中位数,设为a和b,求序列A,B的中位数过程如下:
// 1.若a==b,则a或b即为所求中位数,算法结束。
// 2.若a<b,则舍弃序列A中较小的一部分,同时舍弃序列B中较大的一部分,要求两次舍弃的长度相等。
// 3.若a>b,则舍弃序列A中较大的一部分,同时舍弃序列B中较小的一部分,要求两次舍弃的长度相等。
// 在保留的两个升序序列中,重复过程1),2),3),直到两个序列中均只含有一个元素时为止,较小者即为所求的中位数。
int find_mid_from_A_B_ordered_seq( SeqList &A, SeqList &B )
{
	int s1, d1, m1, s2, d2, m2;
	s1 = 0, d1 = A.length - 1;
	s2 = 0, d2 = A.length - 1;
	while ( s1 != d1 || s2 != d2 )
	{
		m1 = ( s1 + d1 ) / 2;
		m2 = ( s2 + d2 ) / 2;
		if ( A.data[m1] == B.data[m2] )
			return A.data[m1];
		if ( A.data[m1] < B.data[m2] )
		{
			if ( ( s1 + d1 ) % 2 == 0 )	// 元素个数为奇数
				s1 = m1, d2 = m2;
			else
				s1 = m1 + 1, d2 = m2;
		}
		else
		{
			if ( ( s2 + d2 ) % 2 == 0 ) // 元素个数为奇数
				d1 = m1, s2 = m2;
			else
				d1 = m1, s2 = m2 + 1;
		}
	}
	return A.data[s1] < B.data[s2] ? A.data[s1] : B.data[s2];
}

// WP18 12.已知一个整数序列A=(a0,a1,...,an-1),其中0≤ai＜n(0≤i＜n)。若存在ap1=ap2=...apm=x且m>n/2(0≤pk＜n,1≤k≤m),则称x为A的主
// 元素。例如A=(0,5,5,3,5,7,5,5),则5为主元素;又如A=(0,5,5,3,5,1,5,7),则A中没有主元素。假设A中的n个元素保存在一个一维数组中,请设
// 计一个尽可能高效的算法,找出A的主元素。若存在主元素,则输出该元素;否则输出-1。要求:
// (1)给出算法的基本设计思想。
// (2)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。
// 
// 算法思想:
// 算法的策略是从前向后扫描数组元素,标记处一个可能成为主元素的元素Num。然后重新计数，确认Num是否是主元素。
// 算法可分为以下两步:
// 1.选取候选的主元素:依次扫描所给数组中的每个整数,将第一个遇到的整数Num保存到c中,记录Num的出现次数为1;若遇到的下一个整数仍等于
// Num,则计数器加1,否则计数减1;当计数减到0时,将遇到的下一个整数保存到c中,计数重新标记为1,开始新一轮计数,即从当前位置开始重复上述过
// 程,直到扫描完全部数组元素。
// 2.判断c中元素是否是真正的主元素:再次扫描该数组,统计c中元素出现的次数,若大于n/2,则为主元素;否则,序列中不存在主元素
int find_marjor_seq( SeqList &A )
{
	int i, c, count = 1;
	c = A.data[0];
	for ( i = 1; i < A.length; i++ )
	{
		if ( A.data[i] == c )	count++;
		else
		{
			if ( count > 0 )	count--;
			else
			{
				c = A.data[i];
				count = 1;
			}
		}
	}
	if ( count > 0 )
	{
		for ( i = count = 0; i < A.length; i++ )
			if ( A.data[i] == c )	count++;
		if ( count > A.length / 2 )	return c;
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////
// 
// 线性表的链式表示
// 
//////////////////////////////////////////////////////////////////////////

// 头插法建立链表O(n)
LinkList head_insert_create_list(LinkList &L)
{
	LNode *s;
	int x;
	L = ( LinkList ) malloc( sizeof( LNode ) );
    L->next = NULL;
	scanf_s("%d", &x);
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
	minp   = p   = L->next;
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
	while (head->next)
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
	LNode *rA= A, *rB = B;
	LNode *p = A->next;
	A->next = B->next = NULL;
	int i = 0;
	while ( p )
	{
		i++;
		if ( i % 2 )
		{
			rA->next = p;
			rA= p;
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
	LNode *rA= A;
	LNode *p = A->next, *q;
	B->next = NULL;
	while ( p )
	{
		rA->next = p;	// 尾插法
		rA= p;
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
	while (pA&&pB)
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


int main()
{
	while ( true )
	{
		cout << "================SeqList================" << endl;
		{
			int minVal;
			_DCL_SEQ_N( seqList, 10 );
			_CTE( seqList );
			_PFE( del_min_seq( seqList, minVal ) );
			_CTE( seqList );
			_ED;
		}
		{
			_DCL_SEQ_N( seqList, 10 );
			_CTE( seqList );
			_PFE( reverse_seq( seqList, 2, 4 ) );
			_CTE( seqList );
			_ED;
		}
		{
			_DCL_SEQ_N( seqList, 10 );
			_PFE( del_s2t_seq( seqList, 2, 4 ) );
			_CTE( seqList );
			_ED;
		}
		{
			_DCL_SEQ_N( seqList, 10 );
			_PFE( _SORT_SEQ( seqList ) );
			_CTE( seqList );
			_ED;
		}
		{
			_DCL_SEQ_N( seqList, 10 );
			_PFE( del_s2t_ordered_seq( seqList, 2, 4 ) );
			_CTE( seqList );
			_ED;
		}
		{
			_DCL_SEQ_N_P( seqList, 10 );
			_SORT_SEQ_P( seqList );
			_PFE( del_same_ordered_seq( seqList ) );
			_CTE( seqList );
			_ED;
		}
		{
			_DCL_ORDERED_SEQ_N_P( A, 10 );
			_DCL_ORDERED_SEQ_N_P( B, 10 );
			_DCL_SEQ( C );
			_PFE( merge_ab2c_ordered_seq( A, B, C ) );
			_CTE( A );
			_CTE( B );
			_CTE( C );
			_ED;
		}
		{
			_DCL_SEQ_N_P( A, 10 );
			_PFE( exchange_seq( A, 3, 7 ) );
			_CTE( A );
			_ED;
		}
		{
			_DCL_ORDERED_SEQ_N_P( A, 10 );
			_PFE( search_exchange_insert_ordered_seq( A, 3 ) );
			_CTE( A );
			_ED;
		}
		{
			_DCL_SEQ_N_P( A, 10 );
			_PFE( shift_left_seq( A, 4 ) );
			_CTE( A );
			_ED;
		}
		{
			_DCL_ORDERED_SEQ_N_P( A, 10 );
			_DCL_ORDERED_SEQ_N_P( B, 10 );
			_PFVE( find_mid_from_A_B_ordered_seq( A, B ) );
			_ED;
		}
		{
			//A=(0,5,5,3,5,7,5,5),则5为主元素;又如A=(0,5,5,3,5,1,5,7)
			_DCL_SEQ( A( { 0,5,5,3,5,7,5,5 } ) );
			_DCL_SEQ( B( { 0,5,5,3,5,1,5,7 } ) );
			_CTE( A );
			_CTE( B );
			_PFVE( find_marjor_seq( A ) );
			_PFVE( find_marjor_seq( B ) );
			_ED;
		}
		cout << "=======================================" << endl << endl;

		{
			LinkList lst;
			head_insert_create_list( lst );
			del_x_list( lst->next, 3 );
			_CTE( lst->next );
			_ED;
		}


		if ( _getch() == EOF )
			break;
	}
    return 0;
}