#include <stdlib.h>

/// MATRIZ DE ADJACENCIA
typedef struct graph
{
    int quantidadeVertices, quantidadeArestas;
    int **matrizAdjacencia;

} graph;

int **MATRIXInit(int qtdVertices,int valorDeInicializacao)
{
    int **matrix = malloc(qtdVertices*sizeof(int*));

    for(int i = 0; i<qtdVertices; i++)
        matrix[i] = malloc(qtdVertices*sizeof(int));

    for(int i = 0; i<qtdVertices; i++)
        for(int j = 0; j<qtdVertices; j++)
            matrix[i][j] = valorDeInicializacao;

    return matrix;
}

graph *graphInit(int qtdVertices) // inicializacao de grafos representados MATRICIALMENTE
{
    graph *g = malloc(sizeof(graph));
    g->quantidadeVertices = qtdVertices;
    g->quantidadeArestas = 0;
    g->matrizAdjacencia = MATRIXInit(qtdVertices,0);

    return g;
}

/// VETOR DE ARESTAS

typedef struct aresta
{
    int vertice1;
    int vertice2;

} aresta;

aresta inicializaAresta(int v1,int v2)
{
	aresta a;

	a.vertice1 = v1;
	a.vertice2 = v2;

	return a;
}

void insereAresta(graph *g,aresta a)
{
    int v1 = a.vertice1;
    int v2 = a.vertice2;

    if(g->matrizAdjacencia[v1][v2] == 0) g->quantidadeArestas++;

    g->matrizAdjacencia[v1][v2] = 1;
    g->matrizAdjacencia[v2][v1] = 1;

}

void removeAresta(graph *g, aresta a)
{
    int v1 = a.vertice1;
    int v2 = a.vertice2;

    if(g->matrizAdjacencia[v1][v2] == 1) g->quantidadeArestas--;

    g->matrizAdjacencia[v1][v2] = 0;
    g->matrizAdjacencia[v2][v1] = 0;

}

int devolveQuantidadeArestas_E_formaVetorDeArestas(aresta a[],graph *g)
{
    int v1,v2, quantidadeArestas = 0;
    for(v1 = 0; v1 < g->quantidadeVertices; v1++)
		for(v2 = v1+1; v2<g->quantidadeVertices;v2++)
			if(g->matrizAdjacencia[v1][v2] == 1)
				a[quantidadeArestas++] = inicializaAresta(v1,v2);

	return quantidadeArestas;
}

/// LISTA DE ADJACENCIAS

// "celula" representa cada nó de uma lista encadeada
typedef struct celula
{
    int vertice;
    struct celula *prox;
} celula;

typedef struct graph
{
    int quantidadeVertices, quantidadeArestas;
    celula **listaDeAdjacencias;

} graph;

typedef struct aresta
{
    int vertice1;
    int vertice2;

} aresta;

aresta inicializaAresta(int v1,int v2)
{
	aresta a;

	a.vertice1 = v1;
	a.vertice2 = v2;

	return a;
}

celula *criaLE()
{
    celula *novaCelula = malloc(sizeof(celula));
    novaCelula->vertice = -1;
    novaCelula->prox = NULL;

    return novaCelula;
}

void criaAdjacencia(int valorDoVertice, celula *c)
{
    celula *novaCelula = malloc(sizeof(celula));
    novaCelula->vertice = valorDoVertice;
    novaCelula->prox = c->prox;
    c->prox = novaCelula;
}

graph *graphInit(int qtdVertices)
{
    graph *g = malloc(sizeof(graph));
    g->quantidadeVertices = qtdVertices;
    g->quantidadeArestas = 0;
    g->listaDeAdjacencias = malloc(qtdVertices*sizeof(celula));

    for(int i = 0; i< qtdVertices; i++)
        g->listaDeAdjacencias[i] = criaLE();

    return g;
}

void insereAresta(graph *g,aresta a)
{
    int v1 = a.vertice1;
    int v2 = a.vertice2;
    criaAdjacencia(v2, g->listaDeAdjacencias[v1]);
    criaAdjacencia(v1, g->listaDeAdjacencias[v2]);

}


/// funcao remove aresta mal escrita. Reescrever quando tiver tempo para ficar mais legivel.
/// OBS: FUNCAO AINDA NAO TESTADA!
void removeAresta(graph *g,aresta a)
{
	int v1 = a.vertice1;
    int v2 = a.vertice2;

	celula *c1 = g->listaDeAdjacencias[v1];
	celula *c2 = g->listaDeAdjacencias[v2];

	while(c1->prox->vertice!= v2 && c1!= NULL)
		c1 = c1->prox;

	if(c1 == NULL) return; ///nao existe conexao

	while(c2->prox->vertice!= v1 )
		c2 = c2->prox;

	celula *novo1 = c1->prox;
	celula *novo2 = c2->prox;

	c1->prox = novo1->prox;
	c2->prox = novo2->prox;

	free(novo1);
	free(novo2);


}

int devolveQuantidadeArestas_E_formaVetorDeArestas(aresta a[],graph *g)
{
    int quantidadeArestas = 0;
    for(int indiceVertices = 0; indiceVertices<g->quantidadeVertices; indiceVertices++)
		for(celula *indiceCelulas = g->listaDeAdjacencias[indiceVertices] ; indiceCelulas!=NULL ; indiceCelulas = indiceCelulas->prox)
			if(indiceVertices < indiceCelulas -> vertice) a[quantidadeArestas++] = inicializaAresta(indiceVertices,indiceCelulas->vertice);

	return quantidadeArestas;
