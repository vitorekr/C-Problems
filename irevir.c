#include <stdio.h>
#define false 0
#define true 1
typedef int bool;
bool grafo[ 2001 ][ 2001 ];
bool visitados[ 2001 ];
int N, P;

void profundidade( int ponto ){
    if( visitados[ ponto ] == true ){
        return;
    }else{
    visitados[ ponto ] = true;
    for( int i = 1; i <= N; i++ )
        if( grafo[ ponto ][ i ] && !visitados[ i ] ) profundidade( i );
    }
}

int main(){

    scanf(" %d", &N);
    while( N != 0 ){
        scanf(" %d", &P);
        for( int i = 1; i <= N; i++ ){
            visitados[ i ] = false;
            for( int j = 1; j <= N; j++ ){
                grafo[ i ][ j ] = false;
            }
        }

    for( int i = 1; i <= P; i++ ){
        int a, b, op;
        scanf(" %d %d %d", &a, &b, &op);
        if( op == 1 ) grafo[ a ][ b ] = true;
        else{
            grafo[ a ][ b ] = true;
            grafo[ b ][ a ] = true;
        }
    }

    profundidade( 1 );

    bool resposta = true;
    for( int i = 1; i <= N; i++ ){
        if( !visitados[ i ] ){
        resposta = false;
        }
    }

    if( resposta == true ){
        for( int i = 1; i <= N; i++ ){
            visitados[ i ] = false;
            for( int j = i+1; j <= N; j++ ){
                if( grafo[ i ][ j ] && grafo[ j ][ i ] ) continue;
                else if( grafo[ i ][ j ] ){
                    grafo[ j ][ i ] = true; grafo[ i ][ j ] = false;
                }else if( grafo[ j ][ i ] ){
                    grafo[ i ][ j ] = true; grafo[ j ][ i ] = false;
                }
            }
        }

 profundidade( 1 );
 }
 for( int i = 1; i <= N; i++ ){
 if( !visitados[ i ] ){
 resposta = false;
 }
 }

 if( resposta ) printf("1\n");
 else printf("0\n");

 scanf(" %d", &N);
 }

 return 0;
}
