#pragma once
#include "alg_common.h"

/*
* 自己用,节省代码,比cout方便一些
* 函数名: 用途_[ordered]_seq
* 没有ordered就表示无序的
*/
default_random_engine dre( ( unsigned int ) time( 0 ) );


vector<int> _Generate_N_number( int n, int from = 0, int to = 10 )
{
	vector<int> vec;
	uniform_int_distribution<int> di( from, to );
	for ( int i = 0; i < n; i++ )
		vec.push_back( di( dre ) );
	return vec;
}

vector<int> _Sorted_N_number( int n, int from = 0, int to = 10 )
{
	vector<int> vec = _Generate_N_number( n, from, to );
	sort( vec.begin(), vec.end() );
	return vec;
}

#define _ct _countof
#define _PF(func) { cout << #func << ": "; func; }
#define _PFV(func) { cout << #func << ": " << func;}
#define _PFE(func) { _PF(func); _ED; }
#define _PFVE(func)	{ _PFV(func); _ED; }
#define _CTE(seqName) { cout << #seqName << ": "; CTE(seqName); }
#define _CT(seqName) { cout << #seqName << ": "; CT(seqName); }

#define _DCL_SEQ(seqName) SeqList seqName
#define _DCL_SEQ_N(seqName,n) SeqList seqName(_Generate_N_number(n)) 

#define _DCL_ORDERED_SEQ_N(seqName,n) SeqList seqName(_Sorted_N_number(n))

#define _DCL_SEQ_P(seqName) \
	_DCL_SEQ(seqName); \
	_CTE(seqName);
#define _DCL_SEQ_N_P(seqName,n) \
	_DCL_SEQ_N(seqName,n); \
	_CTE(seqName);
#define _DCL_ORDERED_SEQ_N_P(seqName,n) \
	_DCL_ORDERED_SEQ_N(seqName,n); \
	_CTE(seqName);


#define _SORT_SEQ(seqName)	sort(seqName.data, seqName.data + seqName.length)
#define _SORT_SEQ_P(seqName) \
	_SORT_SEQ(seqName); \
	_CT(seqName); \
	cout << "[sorted]\n";

#define _ED cout << endl


template<typename T>
void CT( const T& t ) { cout << t; }
template <typename T, typename... Args>
void CTE( const T& t ) { cout << t << endl; }
template <typename T, typename... Args>
void CT( const T& t, Args... args )
{
	cout << t;
	CT( args... );
}
template <typename T, typename... Args>
void CTE( const T& t, Args... args )
{
	cout << t << endl;
	CT( args... );
}
template <typename T, int N>
void CT( T( &arr )[N], const string &sep = " " )
{
	for ( auto elem : arr )
		cout << elem << sep;
}
template <typename T, int N>
void CTE( T( &arr )[N], const string &sep = " " )
{
	for ( auto elem : arr )
		cout << elem << sep;
	cout << endl;
}

struct SeqList
{
	SeqList() { length = 0; maxSize = 100; }
	SeqList( initializer_list<int> ilz )
	{
		length = ilz.size();
		for ( int i = 0; i < length; i++ )
			data[i] = *( ilz.begin() + i );
		maxSize = 100;
	}
	SeqList( vector<int> vec )
	{
		length = vec.size();
		for ( int i = 0; i < length; i++ )
			data[i] = vec[i];
		maxSize = 100;
	}
	friend ostream& operator << ( ostream& o, const SeqList& seq )
	{
		for ( int i = 0; i < seq.length; i++ )
			o << seq.data[i] << " ";
		return o;
	}
	int data[100];
	int length;
	int maxSize;
};


typedef struct LNode
{
	int data;
	struct LNode *next;
	friend ostream& operator<<( ostream& o, const LNode* node )
	{
		const LNode *p = node;
		while ( p )
		{
			o << p->data;
			if ( p->next )
				o << "->";
			p = p->next;
		}
		return o;
	}
	friend ostream& operator<<( ostream& o, const LNode& node )
	{
		const LNode *p = &node;
		while ( p )
		{
			o << p->data;
			if ( p->next )
				o << "->";
			p = p->next;
		}
		return o;
	}
}LNode, *LinkList;

typedef struct DNode
{
	int data;
	struct DNode *prior, *next;
	int freq;
}DNode, *DLinkList;

// #define MaxSize 50
// typedef struct SLinkList
// {
// 	int data;
// 	int next;
// }SLinkList[MaxSize];
int Length( LinkList& L )
{
	int i = 0;
	LNode *p = L->next;
	while ( p )
	{
		i++;
		p = p->next;
	}
	return i;
}