#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define false 0
#define true 1
typedef int bool;
typedef int TIPOPESO;

int infinity = 2147483647;

typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;
} VERTICE;

typedef struct graph
{
    int quantidadeVertices, quantidadeArestas;
    VERTICE *adj;

} GRAFO;

GRAFO *criaGrafo(int v){
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->quantidadeVertices = v;
    g->quantidadeArestas = 0;
    g->adj = (VERTICE *)malloc(v*sizeof(VERTICE));
    int i;
    for(i = 0; i < v; i++)
        g->adj[i].cab = NULL;
    return g;
}

ADJACENCIA *criaAdj(int v, int peso){
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));

    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;

    return temp;
}

bool criaAresta(GRAFO *g, int vi, int vf, TIPOPESO p){
    if(!g) return false;
    if((vf < 0) || (vf >= g->quantidadeVertices))
        return false;
    if((vi < 0) || (vi >= g->quantidadeVertices))
        return false;

    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = g->adj[vi].cab;
    g->adj[vi].cab = novo;
    g->quantidadeArestas++;
    return true;
}


void inicializaD(GRAFO *g, int *d, int *p, int s){
    int v;

    for(v = 0; v < g->quantidadeVertices; v++){
        d[v] = INT_MAX/2;
        p[v] = -1;
    }
    d[s] = 0;
}

void relaxa(GRAFO *g, int *d, int *p, int u, int v){
    ADJACENCIA *ad = g->adj[u].cab;
    while(ad && ad->vertice != v)
        ad = ad->prox;
    if(ad){
        if(d[v] > d[u] + ad->peso){
            d[v] = d[u] + ad->peso;
            p[v] = u;
        }
    }
}

bool existeAberto(GRAFO *g, int *aberto){
    int i;

    for(i = 0; i < g->quantidadeVertices; i++)
        if(aberto[i]) return true;
    return false;
}

int menorDist(GRAFO *g, int *aberto, int *d){
    int i;
    for(i = 0; i < g->quantidadeVertices; i++)
        if(aberto[i]) break;
    if(i == g->quantidadeVertices) return(-1);

    int menor = i;

    for(i = menor+1; i < g->quantidadeVertices; i++){
        if(aberto[i] && (d[menor] > d[i]))
            menor = i;
    }

    return menor;
}

int *dijkstra(GRAFO *g, int s){
    int *d = (int *)malloc(g->quantidadeVertices*sizeof(int));
    int p[g->quantidadeVertices];
    bool aberto[g->quantidadeVertices];
    inicializaD(g,d, p, s);
    int i;

    for(i = 0; i < g->quantidadeVertices; i++)
        aberto[i] = true;

    while(existeAberto(g, aberto)){
        int u = menorDist(g, aberto, d);
        aberto[u] = false;
        ADJACENCIA *ad = g->adj[u].cab;
        while(ad){
            relaxa(g, d, p, u, ad->vertice);
            ad = ad->prox;
        }
    }
    return d;
}

/*void Dijkstra(GRAFO *g, int source)
{

    int *mature = malloc(g->quantidadeVertices*sizeof(int));
    int *distances = malloc(g->quantidadeVertices*sizeof(int));
    int *parent = malloc(g->quantidadeVertices*sizeof(int));

    for(int v = 0; v < g->quantidadeVertices; v++){
        parent[v] = -1;
        distances[v] = infinity;
        mature[v] = 0;
    }

    parent[source] = source;
    distances[source] = 0;

    while(1){
        int min = infinity;
        int y;

        for(int z = 0; z < g->quantidadeVertices; z++)
        {
            if(mature[z]) continue;
            if(distances[z] < min){
                min = distances[z];
                y = z;
            }
        }

        if(min == infinity) break;

        for(ADJACENCIA *t = g->adj[y].cab; t != NULL; t = t->prox){
            if(mature[t->vertice] == 1) continue;
            if(distances[y] + t->peso < distances[t->vertice]){
                distances[t->vertice] = distances[y] + t->peso;
                parent[t->vertice] = y;
            }
        }
        mature[y] = 1;
    }

    printf("%d\n", distances[g->quantidadeVertices-1]);

}*/




int main(){
    int n, m; //número de pilares no desfiladeiro e o número de pontes, respectivamente.
    int s, t, b; //indicando que existe uma ponte ligando os pilares S e T , e que possui B buracos.

    scanf("%d %d", &n, &m);

    GRAFO *temp = criaGrafo(n+2);

    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &s, &t, &b);
        criaAresta(temp, s, t , b);
        criaAresta(temp, t, s , b);
    }

    int *r = dijkstra(temp, 0);

    /*for(int i = 0; i < n+2; i ++) {
        for(ADJACENCIA *t = temp->adj[i].cab; t != NULL; t = t->prox) {
            printf("vertice:%d\n", t->vertice);
            printf("peso:%d\n", t->peso);
        }
        printf("\n");
    }*/
    //Dijkstra(temp, 0);


    printf("%d\n", r[n+1]);



return 0;
}
