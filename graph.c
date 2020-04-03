#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
#define INFINITIVE 99999
Graph createGraph()
{
	Graph map;
	map.edges = make_jrb();
	map.vertices = make_jrb();
	return map;
}
void addVertex(Graph map, char *id, char *name)
{
	JRB node = jrb_find_str(map.vertices,id);
	if(node == NULL) jrb_insert_str(map.vertices,strdup(id),new_jval_s(strdup(name)));
}
char *getVertex(Graph map, int id)
{
	JRB node = jrb_find_int(map.vertices,id);
	if(node == NULL) return NULL;
	return node->val.s;
}
int hasEdge(Graph map, int v1, int v2)
{
	JRB node = jrb_find_int(map.edges,v1);
	if(node == NULL ) return 0;
	JRB tree = (JRB) node->val.v;
	node = jrb_find_int(tree,v2);
	if(node == NULL ) return 0;
	return 1;
}
void addEdge(Graph map, int v1, int v2, double weight)
{
	if(hasEdge(map,v1,v2)) return;
	JRB node, tree;
	node = jrb_find_int(map.edges,v1);
	if(node == NULL)
	{
		tree = make_jrb();
		jrb_insert_int(map.edges,v1,new_jval_v(tree));
	}
	else  tree = (JRB) (node->val.v);
	jrb_insert_int(tree,v2,new_jval_d(weight));
}
int indegree(Graph map, int v, int *output)
{
	int total=0;
	JRB node,tree;
	jrb_traverse(node,map.edges)
	{
		tree = (JRB)(node->val.v);
		if(jrb_find_int(tree,v) != NULL) output[total++] = node->key.i;
	}
	return total;
}
int outdegree(Graph map, int v, int *output)
{
	int total=0;
	JRB node = jrb_find_int(map.edges,v);
	if(node == NULL) return 0;
	JRB tmp = (JRB) node->val.v;
	jrb_traverse(node,tmp)
	{
		output[total++] = node->key.i;
	}
	return total;
}
double getEdgeValue(Graph map, int v1, int v2)
{
	JRB node = jrb_find_int(map.edges,v1);
	if(node == NULL) return INFINITIVE;
	JRB tree = (JRB) node->val.v;
	node = jrb_find_int(tree,v2);
	if(node == NULL) return INFINITIVE;
	return node->val.d;
}
int number(Graph map)
{
	int total=0;
	JRB node;
	jrb_traverse(node,map.vertices)
	{
		total++;
	}
	return total;
}
double shortestPath(Graph g, int s, int t, int* p)
{
   double d[1000], k[1000], min, w;
   int n, output[100], i, u, v;
   Dllist ptr, node_min, queue;
   JRB node;

   for (i=0; i<1000; i++)
   {
       d[i] = INFINITIVE;
       k[i] = 0; //chua tim duoc duong di tu s den i
   }
   d[s] = 0; p[s] = s;

   //Bo sung tat ca cac dinh cua do thi vao hang doi Q:
   queue = new_dllist();
   jrb_traverse(node, g.vertices)
       dll_append(queue, new_jval_i(jval_i(node->key)));

   while ( !dll_empty(queue) )
   {
      /* get u from the priority queue:
      Tim u la dinh co d[u] nho nhat trong so cac dinh thuoc queue*/
      min = INFINITIVE + 1;
      dll_traverse(ptr, queue) //duyet qua tung dinh v cua queue, tim u la dinh co gia tri d nho nhat
      {
          v = jval_i(ptr->val);
          if (min > d[v])
          {
             min = d[v];
             node_min = ptr;
             u = v;
          }
      }
      k[u] = 1; //da tim duoc ddnn tu s den u
      dll_delete_node(node_min); //xoa u khoi queue vi da tim duoc ddnn tu s den u

      if (u == t) break; // stop at t

      n = outdegree(g, u, output);
      for (i=0; i<n; i++)
      {
          v = output[i];
          if (k[v] == 0) //neu van chua tim duoc ddnn tu s den v
          {
              w = getEdgeValue(g, u, v);
              if ( d[v] > d[u] + w ) //kiem tra xem co giam duoc ddnn tu s den v bang cach di qua canh (u, v) hay ko
              {
                 d[v] = d[u] + w;
                 p[v] = u;
              }
          }//end if
      }//end for
   }//end while
   return d[t];
}
void topologicalSort(Graph map, int *output, int *n) 
{
	Dllist queue = new_dllist();
	JRB node,tmp;
	Dllist abc;
	int banvao[100];
	int v;
	jrb_traverse(node,map.vertices)
	{
		v=jval_i(node->key);
		banvao[v] = indegree(map,v,output);
		if(banvao[v] == 0){
			dll_append(queue,new_jval_i(v));
		} 
	}
	int total=0;
	while(!dll_empty(queue))
	{
		abc = dll_first(queue);
		v= jval_i(abc->val);
		dll_delete_node(abc);
		output[total++] = v;
		tmp = jrb_find_int(map.edges,v);
		if(tmp == NULL) continue;
		JRB tree = (JRB)(tmp->val.v);
		jrb_traverse(tmp,tree)
		{
			int u = tmp->key.i;
			banvao[u]--;
			if(banvao[u] == 0)
				dll_append(queue,new_jval_i(u));
		}
	}
	*n=total;
}
int DFS_DAG(Graph map, int start)
{
	int visited[1000]={};
	int n,output[100],i,u,v;
	Dllist node, stack;
	stack = new_dllist();
	dll_append(stack, new_jval_i(start));
	while(!dll_empty(stack))
	{
		node = dll_last(stack);
		u= jval_i(node->val);
		dll_delete_node(node);
		if(!visited[u])
		{
			visited[u] =1;
			n=outdegree(map,u,output);
			for(i=0;i<n;i++)
			{
				v = output[i];
				if(v == start) return 0;
				if(!visited[v]) dll_append(stack,new_jval_i(v));
			}
		}
	}
	return 1;
}
int DAG(Graph map) // trả về 1 nếu đồ thị ko có chu trình 
{
	int start, notCycle;
	JRB vertex;
	jrb_traverse(vertex,map.vertices)
	{
		start = jval_i(vertex->key);
		printf("Goi DFS xuat phat tu dinh %d \n",start );
		notCycle = DFS_DAG(map,start);
		if(notCycle == 0) return 0;
	}
	return 1;
}
void dropGraph(Graph map)
{
	JRB node, tree;
	jrb_traverse(node,map.edges)
	{
		tree = (JRB) jval_v(node->val);
		jrb_free_tree(tree);
	}
	jrb_free_tree(map.edges);
	jrb_free_tree(map.vertices);
}
