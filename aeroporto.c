#include <stdio.h>
#define MAX_AERO 100

int main()
{
    int a, v, x, y;
    int max, k = 1, i;

    while(scanf("%d%d", &a, &v) && a != 0 && v != 0) {
        int ma[MAX_AERO+1] = {0};
        max = 0;

        for(i = 0; i < v; i++) {
            scanf("%d%d", &x, &y);
            ma[x]++;
            ma[y]++;

            if(max < ma[x] || max < ma[y]){
                if(ma[x] > ma[y]) max = ma[x];
                else max = ma[y];
            }
        }

        printf("Teste %d\n", k++);

        for(i = 1; i <= a; i++) {
            if(ma[i] == max)
                printf("%d ", i);
        }

       printf("\n\n");
    }

    return 0;
}
