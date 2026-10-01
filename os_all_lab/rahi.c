#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 20
#define MAX_THREADS 20

int numbers[ARRAY_SIZE];

typedef struct {
    int start;
    int end;
    int partial_sum;
} ThreadData;

void *calculate_sum(void *argument)
{
    ThreadData *data = (ThreadData *)argument;
    int sum = 0;

    for (int i = data->start; i < data->end; i++) {
        sum = sum + numbers[i];
    }

    data->partial_sum = sum;
    return NULL;
}

int main()
{
    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    int number_of_threads;
    int elements_per_thread;
    int extra_elements;
    int next_start = 0;
    int final_sum = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = i + 1;
    }

    printf("Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Enter the number of threads (1-%d): ", MAX_THREADS);

    if (scanf("%d", &number_of_threads) != 1 ||
        number_of_threads < 1 ||
        number_of_threads > MAX_THREADS) {
        printf("Invalid number of threads.\n");
        return EXIT_FAILURE;
    }

    elements_per_thread = ARRAY_SIZE / number_of_threads;
    extra_elements = ARRAY_SIZE % number_of_threads;

    for (int i = 0; i < number_of_threads; i++) {
        int segment_size = elements_per_thread;

        if (i < extra_elements) {
            segment_size++;
        }

        thread_data[i].start = next_start;
        thread_data[i].end = next_start + segment_size;
        thread_data[i].partial_sum = 0;
        next_start = thread_data[i].end;

        if (pthread_create(&threads[i],
                           NULL,
                           calculate_sum,
                           (void *)&thread_data[i]) != 0) {
            printf("Error creating thread %d.\n", i + 1);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < number_of_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread %d.\n", i + 1);
            return EXIT_FAILURE;
        }

        printf("Thread %d: indices %d to %d, partial sum = %d\n",
               i + 1,
               thread_data[i].start,
               thread_data[i].end - 1,
               thread_data[i].partial_sum);

        final_sum = final_sum + thread_data[i].partial_sum;
    }

    printf("Final sum = %d\n", final_sum);
    return EXIT_SUCCESS;
}
