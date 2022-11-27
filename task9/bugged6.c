/******************************************************************************
* ЗАДАНИЕ: bugged6.c
* ОПИСАНИЕ:
*   Множественные ошибки компиляции
*   Программа должнна была показывать, как можно выполнять параллельный код,
*   используя функции, но что-то пошло не так.
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod()
{
    int i, tid;
    float sum;

    //forgotten parallel word and private(tid)
    #pragma omp parallel for private(tid) reduction(+:sum)
    for (i = 0; i < VECLEN; i++)
    {
        tid = omp_get_thread_num();
        sum = sum + (a[i] * b[i]);
        printf("  tid= %d i=%d\n", tid, i);
    }
    return sum;
}


int main (int argc, char *argv[])
{
    int i;
    float sum;

    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = 1.0 * i;
    sum = 0.0;
    //parallel replaced
    //#pragma omp parallel shared(sum)
    sum = dotprod();

    printf("Sum = %f\n",sum);
}


