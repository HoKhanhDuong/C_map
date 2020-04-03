#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"jrb.h"
#include"jval.h"
#include"dllist.h"
#include"fields.h"

typedef struct $
{
	JRB edges;
	JRB vertices;	
}Graph;
Graph createGraph()
{
	Graph map;
	map.edges = make_jrb();
	map.vertices = make_jrb();
	return map;
}
int hasEdge(Graph map, char *v1, char *v2)
{
	JRB node = jrb_find_str(map.edges,v1);
	if(node == NULL ) return 0;
	JRB tree = (JRB) node->val.v;
	node = jrb_find_str(tree,v2);
	if(node == NULL ) return 0;
	return 1;
}
void Edge(Graph map, char *v1, char *v2, double weight)
{
	if(hasEdge(map,v1,v2)) return;
	JRB node, tree;
	node = jrb_find_str(map.edges,v1);
	if(node == NULL)
	{
		tree = make_jrb();
		jrb_insert_str(map.edges,strdup(v1),new_jval_v(tree));
	}
	else  tree = (JRB) (node->val.v);
	jrb_insert_str(tree,strdup(v2),new_jval_d(weight));
}
void Read_File(Graph map)
{
	IS is = new_inputstruct("input.txt");
	if(is == NULL)
	{
		printf("Can't open file \n");
		exit(0);
	}
	char id[10],name[20];
	int j=0,a=0;
	double tien[10];
	while(get_line(is) > 0 )
	{
		if(is->NF == 2)
		{
			memcpy(id,is->fields[0],3);
			for(int i= 5 ; is->fields[0][i] != '"'; i++)
			{
				name[j++] = is->fields[0][i];
			}
			name[j++] = ' ';
			for(int i=0;is->fields[1][i] != '"'; i++)
			{
				name[j++] = is->fields[1][i];
			}
			name[j] = '\0';
			jrb_insert_str(map.vertices,strdup(id),new_jval_s(strdup(name)));
			j=0;
		}
		else
		{
			tien[a++] = atof(is->fields[2]);
			Edge(map,is->fields[0],is->fields[1],atof(is->fields[2]));
			Edge(map,is->fields[1],is->fields[0],atof(is->fields[2]));
		}
	}
	int visited[10]={0};
	for(int i=0;i<a-1 ;i++)
	{
		for(j=i+1 ;j < a; j++ )
		{
			if(tien[i] == tien[j])
			{
				if(visited[i] == 1) {
					visited[j] = 1;
					break;
				}
				visited[j] = 1;
				JRB node,tree,tmp;
				jrb_traverse(node,map.edges)
				{
					tree = (JRB) node->val.v;
					jrb_traverse(tmp,tree)
					{
						if(tmp->val.d == tien[i])
						{
							printf("%s - %s \n",node->key.s,tmp->key.s );
						}
					}
				}
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	Graph map = createGraph();
	JRB node, tree, tmp;
	int menu,i,t1,t2;
	do
	{
		printf(" $$$$$$$$$$$$$$$$  MENU  $$$$$$$$$$$$$$\n");
		printf("1/Cac chuyen bay co cung gia ve\n 2/So diem bay va chuyen bay\n 3/Cac chuyen bay den tinh\n 4/danh sach cac tinh co nhieu duong bay nhat\n 5/tim duong bay giua 2 tinh\n 6/thanh phan lien thong cua 1 dinh\n 7/dua ra gia cao nhat va thap nhat khi bay giua 2 tinh\n 0/Exit\n");
		scanf("%d",&menu);
		switch(menu)
		{
			case 1:
				Read_File(map);
				break;
		}
	}while(menu!=0);
	return 0;
}