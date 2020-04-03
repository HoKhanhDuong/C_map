#ifndef _GRAPH_
#define _GRAPH_
#include "jrb.h"
#include "jval.h"
#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct $
{
	JRB edges;
	JRB vertices;	
}Graph;
Graph createGraph();
void addVertex(Graph map, char *id, char *name); // thêm vào tập đỉnh 
char *getVertex(Graph mapn, int id); // lấy tên node 
int hasEdge(Graph map, int v1, int v2); // kiểm tra đường nối từ v1->v2
void addEdge(Graph map, int v1, int v2, double weight); // thêm vào tập cạnh 
int indegree(Graph map, int v, int *output); // bán bậc vào 
int outdegree(Graph map, int v, int *output); // bán bậc ra 
double getEdgeValue(Graph map, int v1, int v2); // lấy ra trọng số trên v1->v2
int number(Graph map); // số đỉnh 
double shortestPath(Graph map, int s, int t, int *p); // đường đi ngắn nhất từ s -> t
void topologicalSort(Graph map, int *output, int *n) ; // Trình tự thực hiện công việc
int DFS_DAG(Graph map, int start); 
int DAG(Graph map);
void dropGraph(Graph map); // giải phóng map 
#endif
