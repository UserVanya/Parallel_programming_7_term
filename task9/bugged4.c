/******************************************************************************
 * ЗАДАНИЕ: bugged4.c
 * ОПИСАНИЕ:
 *   Очень простая программа параллельных манипуляций с двумерным массивом
 *   зависимо от количества исполнителей... но с segmentation fault.
 ******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1048

int main (int argc, char *argv[]) 
{
    int nthreads, tid, i, j;
    // 1024 x 1024 array is too large, we must allocate it on heap
    #pragma omp parallel shared(nthreads) private(i, j, tid)
    {
        // allocating array on heap
        double** a = (double**)malloc(sizeof(double*) * N);
        for (int r = 0; r < N; ++r)
            a[r] = (double*)malloc(sizeof(double) * N);
        tid = omp_get_thread_num();
        if (tid == 0) 
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);

        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                a[i][j] = tid + i + j;

        printf("Thread %d done. Last element= %f\n", tid, a[N-1][N-1]);
    } 
}
