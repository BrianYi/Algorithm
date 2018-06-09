#include "alg_common.h"
#include "Stack.h"
ALG_NAMESPACE_USE

/* 
 * 自己用，节省代码，比cout方便一些
 */
template<typename T>
void CT( const T& t ) { cout << t; }
template <typename T, typename... Args>
void CT(const T& t, Args... args )
{
	cout << t;
	CT( args... );
}
template <typename T, int N>
void CT( T( &arr )[N], const string &sep = " ")
{
	for ( auto elem : arr )
		cout << elem << sep;
}

/*
 * 从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删除元素的值。
 * 空出的位置由最后一个元素填补，若顺序表为空则显示出错信息并退出
 */
bool del_min( int A[], int len, int &val )
{
	if ( len == 0 )
		return false;
	val = A[0];
	int pos = 0;
	for ( int i = 1; i < len; i++ )
	{
		if ( A[i] < val )
		{
			val = A[i];
			pos = i;
		}
	}
	A[pos] = A[len - 1];
	len--;
	return true;
}

/*
 * 设计一个高效的算法，讲顺序表的所有元素逆置，要求算法的空间复杂度为O(1)
 */
void Reverse( int A[], int len, int from, int to )
{
	for ( int i = 0; i < ( to - from + 1 ) / 2; i++ )
	{
		swap( A[from + i], A[to - i] );
	}
}



int main()
{
	int A[] = { 3,2,1,5,4 }, iMin;
	del_min( A, _countof( A ), iMin );
	CT( iMin, A );
    return 0;
}