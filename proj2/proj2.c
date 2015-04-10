#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) (a<b ? a : b)

struct node
{
    int info;
    struct node *link;
}*front=NULL,*rear=NULL;
/* FILA */

int V;

struct vertex
{
    struct edge *edgePtr;
}vertex;

struct edge
{
    int vertexIndex;
    int capacity;
    struct edge *edgePtr;
}edge;

struct vertex *graph2,*rgraph2;

void initGraph() {
	int i;
	graph2 = (struct vertex *) malloc(sizeof(*graph2)*V);
	rgraph2 = (struct vertex *) malloc(sizeof(*rgraph2)*V);
	for(i=0;i<V;i++) {
		/* insere vertices */
		graph2[i].edgePtr=NULL;
		rgraph2[i].edgePtr=NULL;
	}
}

void insertEdge(int vertex1, int vertex2,int capac)
{
    struct edge *e1, *e2;
    e1=(struct edge *)malloc(sizeof(*e1));
    e2=(struct edge *)malloc(sizeof(*e2));
    
    e1->vertexIndex=vertex2;
    
    e1->edgePtr=graph2[vertex1].edgePtr;
    e1->capacity=capac;
    graph2[vertex1].edgePtr = e1;
    
    e2->vertexIndex=vertex2;
    
    e2->edgePtr=rgraph2[vertex1].edgePtr;
    e2->capacity=capac;
    rgraph2[vertex1].edgePtr = e2;
    
    
    
}

int searchGraph(int i,int j)
{
	struct edge *e;
	if(rgraph2[i].edgePtr==NULL)
		return 0;
	e=rgraph2[i].edgePtr;
	while(e->vertexIndex!=j) {
		if(e->edgePtr==NULL)
			return 0;
		e=e->edgePtr;
	}
	return e->capacity;
	
}

int searchGraphN(int i,int j)
{
	struct edge *e;
	if(graph2[i].edgePtr==NULL)
		return 0;
	e=graph2[i].edgePtr;
	while(e->vertexIndex!=j) {
		if(e->edgePtr==NULL)
			return 0;
		e=e->edgePtr;
	}
	return e->capacity;
	
}

void changeGraph(int i,int j,int value)
{
	struct edge *e;
	if(rgraph2[i].edgePtr==NULL)
		return;
	e=rgraph2[i].edgePtr;
	while(e->vertexIndex!=j) {
		if(e->edgePtr==NULL)
			return;
		e=e->edgePtr;
	}
	e->capacity = value;
	
}
int emptyQ()
{
    if(front==NULL)
        return 1;
    else
        return 0;

}

int popQ()
{
    struct node *tmp;
    int item;
    if( emptyQ( ) )
    {
        
        exit(1);
    }
    tmp=front;
    item=tmp->info;
    front=front->link;
    free(tmp);
    return item;
}

void pushQ(int item)
{
    struct node *tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    if(tmp==NULL)
    {
      
        return;
    }
    tmp->info = item;
    tmp->link=NULL;
    if(front==NULL)      
        front=tmp;
else
    rear->link = tmp;
    rear=tmp;
}

int frontQ()
{
    if( emptyQ( ) )
    {

        exit(1);
    }
    return front->info;
}

int bfs(int s, int t, int parent[])
{

	int *visited;
	int u,v;
	visited = (int*)calloc(V,sizeof(int));
	pushQ(s);
	visited[s] = 1;
	parent[s] = -1;
	/*loop da BFS*/
	while (emptyQ()==0)
	{
		u = frontQ();
		
		popQ();
		
		for(v=0;v<V; v++)
		{
	
			if(visited[v]==0 && searchGraph(u,v) > 0)
			{
				pushQ(v);
				parent[v] = u;
				visited[v] = 1;
			}
		}
		
	}
	return(visited[t]);

}

void dfs(int s, int visited[])
{
	visited[s] = 1;
	int i;
	for(i = 0; i < V; i++)
		if(searchGraph(s,i)>0 && visited[i]==0)
			dfs(i, visited);
}

int minCut(int s, int t)
{
	int cortes = 0;
	int u,v;
	int path_flow = INT_MAX;
	int parent[V];
	int act1,act2;
	while (bfs(s, t, parent)==1)
	{
		for(v=t; v!=s; v=parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, searchGraph(u,v));
		}
		/*encontra max flow... corre ford fulkerson on top */
		for (v=t; v!= s; v=parent[v])
		{
			u = parent[v];
			act1 = searchGraph(u,v) - path_flow;
			changeGraph(u,v,act1);
			act2 = searchGraph(v,u) + path_flow;
			changeGraph(v,u,act2);
		}
	}

	
	/*flow e maximo agr, encontrar vertices //atingiveis a partir de s*/
	int *visited;
	visited = (int*)calloc(V,sizeof(int));
	dfs(s, visited);
	
	/*imprimir arestas de reachable p n reachable 
	no caminho original*/
	int i,j;
	for(i=0; i < V; i++) {
		for(j = 0; j < V; j++) {
			if(visited[i]==1 && visited[j]==0 && searchGraphN(i,j)>0)
				cortes++;
		}
	}
	return cortes;
}

int main() {
	/*  Criação do Grafo */
	int i,j,k,arcos,u,v,np,nrpontos,outnr;
	scanf("%d", &V); /*nr de vertices */
	scanf("%d", &arcos); /*nr de arcos, nr de partilhas */
	initGraph();
	
	for(i=0;i<arcos;i++) 
	{
		scanf("%d",&u);
		scanf("%d",&v);
		insertEdge(u,v,1);
		insertEdge(v,u,1);
	} 
	int *pontos;
	int *output;
	int *npout;
	int lulz; 
	
	scanf("%d",&np);
	npout = (int*) malloc(sizeof(int)*np);
	for(i=0;i<np;i++)
		npout[i] = INT_MAX;
	for(i=0,lulz=0;i<np;i++) {
		scanf("%d",&nrpontos);
		pontos = (int*)calloc(nrpontos,sizeof(int));
		for(j=0;j<nrpontos;j++)
			scanf("%d",&pontos[j]);
		/*faz sort do array e implementa min do mincut entre todos
		Aloca memoria p resultado */ 
		for(j=0,outnr=0;j<nrpontos-1;j++)
			for(k=j+1;k<nrpontos;k++) {
				outnr++;
			}
		output = (int*)calloc(outnr,sizeof(int));
		for(j=0;j<nrpontos-1;j++)
			for(k=j+1;k<nrpontos;k++) {
				output[lulz] = minCut(pontos[j], pontos[k]); 
				lulz++;
			}
		/*encontra valor minimo no array */
		for(j=0;j<outnr;j++)
			if(output[j] < npout[i])
				npout[i] = output[j];
		lulz = 0;
	}
	for(i=0;i<np;i++)
		printf("%d\n",npout[i]);
	return 0;
}