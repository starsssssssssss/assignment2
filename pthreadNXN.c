#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_func(void* arg) {
    int thread_id = *((int*) arg);
    printf("Hello from thread %d\n", thread_id);
    return NULL;
}

int main() {
    int num_threads = 2;

    // Allocate memory for thread IDs
    int* thread_ids = (int*) malloc(sizeof(int) * num_threads);

    // Create threads
    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    free(threads);
    free(thread_ids);

    return 0;
}