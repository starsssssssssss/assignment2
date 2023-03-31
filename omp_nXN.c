#include <stdio.h>
#include <omp.h>

#define N 2
#define M 2
#define K 2

int main()
{
    int i, j, k;
    int A[N][M] = { {1, 2}, {7, 8} };
    int B[M][K] = { {3, 5}, {4, 6} };
    int C[N][K];

    #pragma omp parallel shared(A,B,C) private(i,j,k)
    {
        int id = omp_get_thread_num();      // Get the ID of the current thread
        int n_threads = omp_get_num_threads();  // Get the total number of threads

        // Divide the computation of rows of C among the threads
        int start = id * N / n_threads;
        int end = (id + 1) * N / n_threads;
        for (i = start; i < end; i++) {
            for (j = 0; j < K; j++) {
                C[i][j] = 0;
                for (k = 0; k < M; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    printf("Result matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < K; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}