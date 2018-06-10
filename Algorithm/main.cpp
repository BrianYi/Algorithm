#include "alg_common.h"
#include "Stack.h"
ALG_NAMESPACE_USE

/* 
 * 自己用,节省代码,比cout方便一些
 */

#define _ct _countof
#define _PF(func) { cout << #func << ": " << endl; func; }
//#define PF(func)  _PF(#func)
template<typename T>
void CT( const T& t ) { cout << t; }
template <typename T, typename... Args>
void CTE( const T& t ) { cout << t << endl; }
template <typename T, typename... Args>
void CT(const T& t, Args... args )
{
	cout << t;
	CT( args... );
}
template <typename T, typename... Args>
void CTE(const T& t, Args... args )
{
	cout << t << endl;
	CT( args... );
}
template <typename T, int N>
void CT( T( &arr )[N], const string &sep = " ")
{
	for ( auto elem : arr )
		cout << elem << sep;
}
template <typename T, int N>
void CTE( T( &arr )[N], const string &sep = " ")
{
	for ( auto elem : arr )
		cout << elem << sep;
	cout << endl;
}

struct SeqList
{
	SeqList( initializer_list<int> ilz ) 
	{
		length = ilz.size(); 
		for ( int i = 0; i < length; i++ )
			data[i] = *( ilz.begin() + i );
	}
	friend ostream& operator << ( ostream& o , const SeqList& seq)
	{
		for ( int i = 0; i < seq.length; i++ )
			o << seq.data[i] << " ";
		return o;
	}
	int data[100];
	int length;
};

// WP18 1.从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删除元素的值。空出的位置由最后一个元素填补,若顺序表为空则显示出错信
// 息并退出。
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
void reverse_seq( SeqList &L, int from, int to )
{
	for ( int i = 0; i < ( to - from + 1 ) / 2; i++ )
	{
		swap( L.data[from + i], L.data[to - i] );
	}
}

// WP18 3.长度为n的顺序表L,编写一个时间复杂度为O(n),空间复杂度为O(1)的算法,该算法删除线性表中所有值为x的数据元素。
// 解法:用k记录顺序表L中不等于x的元素个数(即需要保存的元素个数),边扫描L边统计k,并将不等于x的元素向前放置k位置上,最后修改L的长度。
void del_x_shuffled_seq( SeqList &L, int x )
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
// 算法思想:先寻找值大于等于s的第一个元素(第一个删除的元素),然后寻找值>t的第一个元素(最后一个删除的元素的下一个元素),要将这段元素删
// 除,则只需直接将后面的元素前移即可。
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
	L.length = i + 1;
	return true;
}

// WP18 5.从顺序表中删除其值在给定值s与t之间(包含s和t,要求s<t)的所有元素,如果s或t不合理或者顺序表为空则显示出错信息并退出运行。
// 算法思想:从前向后扫描顺序表L,用k记录下元素值在s到t之间元素的个数(出世时k=0)。对于当前扫描的元素,若其值不在s到t之间,则前移k个位
// 置;否则执行k++。由于这样每个不在s到t之间的元素仅移动一次,所以算法效率高。
bool del_s2t_shuffled_seq( SeqList &L, int s, int t )
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

// WP18 7.将两个有序顺序表合并成一个新的有序顺序表,使表中所有元素的值均不同。

// WP18 8.已知在一维数组A[m+n]中依次存放着两个线性表(a1,a2,a3,...,am)和(b1,b2,b3,...,bn)。试编写一个函数,将数组中两个顺序表的位
// 置互换,即将(b1,b2,b3,...,bn)放在(a1,a2,a3,...,am)的前面。

// WP18 9.线性表(a1,a2,a3,...,an)中元素递增有序且按顺序存储于计算机内。要求设计一算法完成用最少时间在表中查找数值为x的元素,若找到
// 将其余后继元素位置相交换,若找不到将其插入表中并使表中元素仍递增有序。

// WP18 10.设将n(n>1)个整数存放到一维数组R中。试设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移p(0<p<n)个位 
// 置,即将R中的数据由(X0,X1,...,Xn-1)变换为(Xp,Xp+1,...,Xn-1,X0,X1,...,Xp-1)。要求:
// (1)给出算法的基本设计思想。
// (2)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。

// WP18 11.一个长度为L(L≥1)的升序序列S,处在⌈L/2⌉个位置的数称为S的中位数。例如,若序列S1=(11,13,15,17,19),则S1的中位数是15,两个
// 序列的中位数是含它们所有原色的升序序列的中位数。例如,S2=(2,4,6,8,20),则S1和S2的中位数是11。现在有两个等长升序序列A和B,试设计一
// 个在时间和空间两方面都尽可能高效的算法,找出两个序列A和B的中位数。要求:
// (1)给出算法的基本设计思想。
// (2)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。

// WP18 12.已知一个整数序列A=(a0,a1,...,an-1),其中0≤ai＜n(0≤i＜n)。若存在ap1=ap2=...apm=x且m>n/2(0≤pk＜n,1≤k≤m),则称x为A的主
// 元素。例如A=(0,5,5,3,5,7,5,5),则5为主元素;又如A=(0,5,5,3,5,1,5,7),则A中没有主元素。假设A中的n个元素保存在一个一维数组中,请设
// 计一个尽可能高效的算法,找出A的主元素。若存在主元素,则输出该元素;否则输出-1。要求:
// (1)给出算法的基本设计思想。
// (2)根据设计思想,采用C或C++或Java语言描述算法,关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。
int main()
{
	int minVal;
	SeqList seqList( { 5,7,1,1,2,3,4 } );
	_PF(CTE( seqList ));
	_PF(del_min_seq( seqList, minVal ));
	_PF(CTE( seqList ));
	_PF(reverse_seq( seqList, 2, 4 ));
	_PF(CTE( seqList ));
	_PF(del_s2t_shuffled_seq( seqList, 2, 4 ));
	_PF(sort( seqList.data, seqList.data + seqList.length ));

    return 0;
}