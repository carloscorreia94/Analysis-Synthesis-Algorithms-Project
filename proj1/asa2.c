#include <stdio.h>
#include <stdlib.h>
#define min(a, b) (a<b ? a : b)

struct vertex
{
    struct edge *edgePtr;
    int desc;
    int lowlink;
    int flag;
    int scc_id;
    int visitado;
}vertex;

struct edge
{
    int vertexIndex;
    struct edge *edgePtr;
}edge;

struct item {
	int value;
	struct item *next;
};

/* FIM DA DEF DE ESTRUTURAS

DEF VARIAVEIS */
struct vertex *graph;
int visited = 0;
int grupos = 0;
int nrPessoas;
int maiorGrupo;
int partilham;
int lol = 0;
/* inicializa a pilha */
struct item* top = NULL;

void initGraph() {
	int i;
	graph = (struct vertex *) malloc(sizeof(*graph)*nrPessoas);
	for(i=0;i<nrPessoas;i++) {
		/* insere vertices */
		graph[i].edgePtr=NULL;
		graph[i].desc=-1;
		graph[i].scc_id=-1;
		graph[i].visitado=-1;
	}
}

void insertEdge(int vertex1, int vertex2)
{
    struct edge *e1;
    e1=(struct edge *)malloc(sizeof(*e1));
    
    e1->vertexIndex=vertex2;
    
    e1->edgePtr=graph[vertex1].edgePtr;
    
    graph[vertex1].edgePtr = e1;
    
}
void init() {
	top = NULL;
}

void push(int value) {
	
	struct item *new;
	
	graph[value].flag = 1;
	
	new = (struct item *) malloc(sizeof(struct item));
	new->value = value;
	new->next = top;
	top = new;
}

int is_empty() {
	return top == NULL;
}


int pop(int scc) {
	int value;
	struct item *old;
	
	if(!is_empty()) {
		value = top->value;
		graph[value].flag = 0;
		graph[value].scc_id = scc;
		old = top;
		top = top->next;
		free(old);
		return value;
	}
	else
		return -1;
}

int test_partilha(int count,int popvalue,int raiz) {	
	int temp;
	struct edge *e;
	graph[popvalue].visitado = raiz;
	if(graph[popvalue].scc_id!=graph[raiz].scc_id) {
		return 0;
	}
	if(raiz == popvalue && lol!=0) {
		return 1;
	}
	lol=1;
	e=graph[popvalue].edgePtr;
	
	while(e) {
		temp = e->vertexIndex;

		if(graph[temp].visitado!=raiz) {

			if(test_partilha(count,temp,raiz)==0)
				return 0; 
			
		}
		e=e->edgePtr;
	}

		return 1;
}
void TarjanVisit(int i) {
	
	int j,count; 
	struct edge *e;
	
	int popvalue;
	
	graph[i].desc = visited;
	graph[i].lowlink = visited;
	visited++;
	push(i);

	
	e=graph[i].edgePtr;
	
	while(e)
	{
		/*/estamos dentro do ciclo for each v E Adj[u] */
		j = e->vertexIndex; /*/indice do vertice dentro do ciclo de adj */
		 if(graph[j].desc == -1 || graph[j].flag == 1) {
			if(graph[j].desc == -1) {
				TarjanVisit(j);
			}
		
			
			graph[i].lowlink = min(graph[i].lowlink,graph[j].lowlink);
		 }
			e=e->edgePtr;
		}
		if(graph[i].lowlink == graph[i].desc) {
			count = 0;
			do {
				popvalue = pop(grupos); 
				count++;
			}while(i!=popvalue);
			partilham = partilham + test_partilha(count,popvalue,popvalue);
			lol = 0;
			if(count > maiorGrupo) { maiorGrupo = count; }
			grupos++;
		}
		
	}
	
int main()
{
	/*Criação do Grafo */
	int nrPartilhas,i,pessoa,partilha;
	scanf("%d", &nrPessoas); /*nr de vertices */
	scanf("%d", &nrPartilhas); /*nr de arcos, nr de partilhas */
	initGraph();
	for(i=0;i<nrPartilhas;i++) 
	{
		scanf("%d",&pessoa);
		scanf("%d",&partilha);
		insertEdge(pessoa-1,partilha-1); /* valor no array a contar de 0 */
	} 
	/*1º passo - visited a 0 */
	init(); /*inicializa a pilha */
	
	/* initgraph ja poe tempo de descoberta a -1 */
	
	 for(i=0;i<nrPessoas;i++) {
		if(graph[i].desc==-1)
			TarjanVisit(i);
	}
	printf("%d\n",grupos); 
	printf("%d\n",maiorGrupo);
	printf("%d\n",partilham);
    return 0;
}

