#include <stdio.h>

typedef int Item;
static Item pq[100005];
static Item qp[100005];
static int N;
int *vetor;
void fixDown(Item *pq, int k, int N);
void fixUp(Item *pq, int k);

#define less(A, B) (vetor[A] > vetor[B])

int exch(int i, int j) {
    int t;
    t = qp[i];
    qp[i] = qp[j];
    qp[j] = t;
    pq[qp[i]] = i;
    pq[qp[j]] = j;
}

void PQinit(int maxN) {
    N = 0;
}

int PQespiamin() {
    return vetor[pq[1]];
}

void PQchange(int k) {
    fixUp(pq, qp[k]);
    fixDown(pq, qp[k], N);
}

int PQempty() {
    return N == 0;
}

void PQinsert(Item k) {
    qp[k] = ++N;
    pq[N] = k;
    fixUp(pq, N);
}

Item PQdelmin() {
    exch(pq[1], pq[N]);
    fixDown(pq, 1, N-1);
    return pq[N--];
}

void fixUp(Item *pq, int k) {
    while(k > 1 && less(pq[k/2], pq[k])) {
        exch(pq[k], pq[k/2]);
        k = k/2;
    }
}

void fixDown(Item *pq, int k, int N) {
    int j;
    while(2 * k <= N) {
        j=2*k;
        if(j<N && less(pq[j],pq[j+1]))
            j++;
        if(!less(pq[k],pq[j]))
            break;
        exch(pq[k],pq[j]);
        k=j;
    }
}

void resolve(int n, int k, int *v) {
    int maisvelho = 0, i;
    int nexti = k;
    vetor = v;
    PQinit(n);
    for(i = 0; i < k; i ++) {
        PQinsert(i);
    }
    printf("%d", PQespiamin());
    v[maisvelho] = 0;
    PQchange(maisvelho);
    PQdelmin();
    maisvelho ++;
    PQinsert(nexti);
    nexti ++;
    while(nexti <= n) {
        printf(" %d", PQespiamin());
        v[maisvelho] = 0;
        PQchange(maisvelho);
        PQdelmin();
        maisvelho ++;
        PQinsert(nexti);
        nexti ++;
    }
    printf("\n");
}

int main() {
    int v[100005];
    int n, k, i;
    while(scanf("%d%d", &n, &k) == 2 && n !=0 && k != 0) {
        for(i = 0; i < n; i ++) {
            scanf("%d", &v[i]);
        }
        resolve(n, k, v);
    }
}
