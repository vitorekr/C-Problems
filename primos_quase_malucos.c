#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

typedef struct parametro_thread
{
  int n;
  int tid;
  int result;
} THREAD;

int a, b, resultadoA, resultadoB;
THREAD t1, t2;

int calcule_sequaseprimo_maluco(int number){
    int divisor;
    float root;
    int count=0;

    root = floor(sqrt(number));


    for(divisor = 3; divisor < root; divisor += 2){
        if((number%divisor) == 0 && divisor > 10){
           //printf("%d ", divisor);
            count++;
        }else if((number%divisor) == 0 && divisor <= 10){
            return count = 0;
        }
    }

    if (number == 1 || number % 2 == 0)
        return count = 0;

    if (count >= 10)
        return count;

    //printf("\n%d", count);
    return count = 0;
}


void *thread1(void *p)
{
    while(calcule_sequaseprimo_maluco(t1.n) <= 10)
        t1.n++;

    resultadoA = t1.n;
}

void *thread2(void *p)
{
    while (calcule_sequaseprimo_maluco(t2.n) <= 10)
        t2.n++;
    resultadoB = t2.n;
}

int main(void)
{
    int n;
    pthread_t th1, th2;
    scanf("%d", &n);
    int *param = (int *)malloc(2 * sizeof(int));

    while(1)
    {
        if (scanf("%d", &t1.n) == EOF)
            break;

        t1.n = n;
        param[0] = t1.n;
        pthread_create(&th1, NULL, &thread1, param);

        if (scanf("%d", &t2.n) == EOF){
            pthread_join(th1, NULL);
            printf("%d\n", resultadoA);
            break;
        }

        t2.n = n;
        param[1] = t2.n;
        pthread_create(&th2, NULL, &thread2, param);

        pthread_join(th1, NULL);
        pthread_join(th2, NULL);

        printf("%d\n%d\n", t1.result, t2.result);
    }

    return 0;
}
