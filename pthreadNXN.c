#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3

int A[M][K] = {{1, 2}, {7, 8}, {4, 6}};
int B[K][N] = {{3, 4, 1}, {5, 6, 1}};
int C[M][N];

struct thread_args {
    int start_row;
    int end_row;
};

void* thread_func(void* arg) {
    struct thread_args* args = (struct thread_args*) arg;

    for (int i = args->start_row; i < args->end_row; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return NULL;
}

int main() {
    int num_threads = 2;

    // Allocate memory for thread IDs and args
    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * num_threads);
    struct thread_args* thread_args_list = (struct thread_args*) malloc(sizeof(struct thread_args) * num_threads);

    // Create threads
    int chunk_size = M / num_threads;
    for (int i = 0; i < num_threads; i++) {
        thread_args_list[i].start_row = i * chunk_size;
        thread_args_list[i].end_row = (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, thread_func, &thread_args_list[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result matrix
    printf("Result matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Clean up
    free(threads);
    free(thread_args_list);

    return 0;
}
