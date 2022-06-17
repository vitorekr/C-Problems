#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define false 0
#define true 1
typedef int bool;
typedef int TIPOPESO;

typedef struct celula
{
    int vertice;
    int peso;
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
    int peso;

} aresta;

aresta inicializaAresta(int v1,int v2, int pesoDaAresta)
{
    aresta a;

    a.vertice1 = v1;
    a.vertice2 = v2;
    a.peso = pesoDaAresta;


    return a;
}

void criaAdjacencia(int valorDoVertice, celula *noCabeca, int peso)
{
    celula *novaCelula = malloc(sizeof(celula));
    novaCelula->vertice = valorDoVertice;
    novaCelula->peso = peso;
    novaCelula->prox = noCabeca->prox;
    noCabeca->prox = novaCelula;
}

void insereAresta(graph *g,aresta a)
{
    int peso = a.peso;
    int v1 = a.vertice1;
    int v2 = a.vertice2;
    criaAdjacencia(v2, g->listaDeAdjacencias[v1], peso);
    criaAdjacencia(v1, g->listaDeAdjacencias[v2], peso);

}

celula *criaNoCabeca(int vertice)
{
    celula *novaCelula = malloc(sizeof(celula));
    novaCelula->vertice = vertice;
    novaCelula->prox = NULL;

    return novaCelula;
}


graph *graphInit(int qtdVertices)
{
    int i;
    graph *g = malloc(sizeof(graph));
    g->quantidadeVertices = qtdVertices;
    g->quantidadeArestas = 0;
    g->listaDeAdjacencias = malloc(qtdVertices*sizeof(celula));

    for(i = 0; i< qtdVertices; i++)
        g->listaDeAdjacencias[i] = criaNoCabeca(i);

    return g;
}

typedef struct fila
{
    aresta aAresta;
    struct fila *prox;

} fila;

fila *criaFila()
{
    fila *novaFila = malloc(sizeof(fila));

    novaFila->prox = novaFila;
    novaFila->aAresta.vertice1 = -1;
    novaFila->aAresta.vertice2 = -1;

    return novaFila;
}

void enfileira(fila **f, aresta a)
{
    fila *novaCelula = malloc(sizeof(fila));
    novaCelula->prox = (*f)->prox;
    (*f)->prox = novaCelula;
    (*f)->aAresta.vertice1 = a.vertice1;
    (*f)->aAresta.vertice2 = a.vertice2;

    *f = novaCelula;
    (*f)->aAresta.vertice1 = -1;
    (*f)->aAresta.vertice2 = -1;
}

void desenfileira(fila **f)
{
    fila *novaCelula = malloc(sizeof(fila));
    novaCelula = (*f)->prox;
    if(novaCelula->aAresta.vertice1 == -1) /// FILA VAZIA!
    {
        return;
    }

    (*f)->prox = novaCelula->prox;
    free(novaCelula);

}

void BFS_buscaEmLargura(graph *g, aresta a, int *verticesJaVisitados)
{
    fila *f = criaFila();

    int v2 = a.vertice2;
    verticesJaVisitados[v2] = 1;

    enfileira(&f,a);

    while(f->prox->aAresta.vertice1!=-1 && f->prox->aAresta.vertice2 != -1) /// FILA VAZIA!
    {
        a.vertice1 = f->prox->aAresta.vertice1;
        a.vertice2 = f->prox->aAresta.vertice2;
        desenfileira(&f);
        v2 = a.vertice2;

        for(celula *indiceVertices = g->listaDeAdjacencias[v2]->prox; indiceVertices!=NULL; indiceVertices = indiceVertices->prox)
        {
            int v1 = indiceVertices->vertice;
            if(verticesJaVisitados[v1] == 0)
            {
                aresta novaAresta;
                novaAresta.vertice1 = v2;
                novaAresta.vertice2 = v1;

                enfileira(&f,novaAresta);
                verticesJaVisitados[v1] = 1;

            }
        }
    }
}



/*)void DFS_buscaEmProfundidade_RECURSIVA(graph *g, aresta a, int *verticesJaVisitados)
{
    int v2 = a.vertice2;
    verticesJaVisitados[v2] = 1;

    for(celula *indiceVertices = g->listaDeAdjacencias[v2]->prox; indiceVertices!=NULL; indiceVertices = indiceVertices->prox)
    {
        int v1 = indiceVertices->vertice;
        if(verticesJaVisitados[v1] == 0){
            aresta novaAresta;
            novaAresta.vertice1 = v2;
            novaAresta.vertice2 = v1;
            DFS_buscaEmProfundidade_RECURSIVA(g, novaAresta, verticesJaVisitados);
        }
    }
}*/

int main(){
    int e, l;
    int x, y;
    int k = 1;
    graph *temp;
    aresta a;


    while(scanf("%d%d", &e, &l) && e != 0 && l != 0){
        temp = graphInit(e);
        int *verticesJaVisitados = malloc(sizeof(int)*e);

        for(int i = 0; i < temp->quantidadeVertices; i++){
            verticesJaVisitados[i] = 0;
        }

        for(int i = 0; i < l; i++){
            scanf("%d%d", &x, &y);
            x--;
            y--;
            a = inicializaAresta(x, y, 0);
            insereAresta(temp, a);
            //printf("oi\n");

        }


        printf("Teste %d\n", k++);
        BFS_buscaEmLargura(temp, a, verticesJaVisitados);
        //DFS_buscaEmProfundidade_RECURSIVA(temp, a, verticesJaVisitados);
        int cont = 0;
        for(int i = 0; i < temp->quantidadeVertices; i++){
            //printf("%d", verticesJaVisitados[i]);
            if(verticesJaVisitados[i] == 0){
                cont++;
                break;
            }
        }

        if(cont == 0)
            printf("normal\n");
        else
            printf("falha\n");



        free(verticesJaVisitados);

        printf("\n\n");
    }


return 0;
}
