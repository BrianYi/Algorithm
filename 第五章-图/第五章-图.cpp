// 第五章-图.cpp : Defines the entry point for the console application.
// 
// 
#include "stdafx.h"
// 
// #define MaxVertexNum 100
// typedef char VertexType;
// typedef int EdgeType;
// 
// 图的邻接矩阵存储结构
// typedef struct
// {
// 	VertexType Vex[MaxVertexNum];
// 	EdgeType Edge[MaxVertexNum][MaxVertexNum];
// 	int vexnum, arcnum;
// }MGraph;
// 
// 图的邻接表存储结构
// typedef struct ArcNode	// 边表节点
// {
// 	int adjvex;
// 	struct ArcNode *next;
// 	// InfoType info;
// }ArcNode;
// typedef struct VNode	// 顶点表节点
// {
// 	VertexType data;
// 	ArcNode *first;
// }VNode, AdjList[MaxVertexNum];
// typedef struct			// 邻接表
// {
// 	AdjList vertices;
// 	int vexnum, arcnum;
// }ALGraph;
// 
// 邻接表转邻接矩阵
// void Convert( ALGraph &G, int arc[][] )
// {
// 	for ( int i = 0; i < G.vexnum; i++ )
// 	{
// 		ArcNode *p = G.vertices[i].first;
// 		while ( p )
// 		{
// 			arc[i][p->adjvex] = 1;
// 			p = p->next;
// 		}
// 	}
// }
// 
// #define MAX_VERTEX_NUM 100
// 广度优先搜索
// bool visited[MAX_VERTEX_NUM];
// void BFSTraverse( MGraph G )
// {
// 	// 初始化标记数组visited
// 	for ( int i = 0; i < G.vexnum; i++ )
// 		visited[i] = FALSE;
// 	// 初始化队列Q
// 	InitQueue( Q );
// 	// for BFS图的所有连通分量 
// 	for ( int i = 0; i < G.vexnum; i++ )
// 		if ( !visited[i] )
// 			BFS( G, i );
// }
// 
// void BFS( MGraph G, int v )
// {
// 	// 访问顶点并标记,顶点入队
// 	visit( v );
// 	visited[v] = TRUE;
// 	EnQueue( Q, v );
// 	
// 	// while层序遍历连通分量
// 	while ( !IsEmpty( Q ) )
// 	{
// 		// 出队顶点
// 		DeQueue( Q, v );
// 		// for找未访问过的邻接点
// 		for ( w = FirstNeighbor( G, v ); w >= 0; w = NextNeighbor( G, v, w ) )
// 		{
// 			// 访问邻接点并标记,邻接点入队
// 			if ( !visited[w] )
// 			{
// 				visit[w];
// 				visited[w] = TRUE;
// 				EnQueue( Q, w );
// 			}
// 		}
// 	}
// }
// 
// 
// 
// int main()
// {
//     return 0;
// }

