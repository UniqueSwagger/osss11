#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int threadId;
    int startIndex;
    int endIndex;
    int *array;
    long long partialSum;
} ThreadData;

void *calculatePartialSum(void *argument) {
    ThreadData *data = (ThreadData *)argument;

    data->partialSum = 0;

    for (int i = data->startIndex; i < data->endIndex; i++) {
        data->partialSum += data->array[i];
    }

    printf(
        "Thread %d processed indices %d to %d. Partial sum = %lld\n",
        data->threadId,
        data->startIndex,
        data->endIndex - 1,
        data->partialSum
    );

    return NULL;
}

int main(void) {
    int arraySize;
    int threadCount;

    printf("Enter array size: ");

    if (scanf("%d", &arraySize) != 1) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter number of threads: ");

    if (scanf("%d", &threadCount) != 1) {
        printf("Invalid thread count.\n");
        return 1;
    }

    if (arraySize <= 0 || threadCount <= 0) {
        printf("Array size and thread count must be positive.\n");
        return 1;
    }

    if (threadCount > arraySize) {
        printf("Thread count cannot be greater than array size.\n");
        return 1;
    }

    int *array = malloc(arraySize * sizeof(int));
    pthread_t *threads = malloc(threadCount * sizeof(pthread_t));
    ThreadData *threadData = malloc(threadCount * sizeof(ThreadData));

    if (array == NULL || threads == NULL || threadData == NULL) {
        printf("Memory allocation failed.\n");

        free(array);
        free(threads);
        free(threadData);

        return 1;
    }

    for (int i = 0; i < arraySize; i++) {
        array[i] = i + 1;
    }

    printf("\nInitialized array:\n");

    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }

    printf("\n\n");

    int baseSegmentSize = arraySize / threadCount;
    int remainingElements = arraySize % threadCount;
    int currentStart = 0;

    for (int i = 0; i < threadCount; i++) {
        int segmentSize = baseSegmentSize;

        if (i < remainingElements) {
            segmentSize++;
        }

        threadData[i].threadId = i;
        threadData[i].startIndex = currentStart;
        threadData[i].endIndex = currentStart + segmentSize;
        threadData[i].array = array;
        threadData[i].partialSum = 0;

        int status = pthread_create(
            &threads[i],
            NULL,
            calculatePartialSum,
            &threadData[i]
        );

        if (status != 0) {
            printf("Failed to create thread %d.\n", i);

            for (int j = 0; j < i; j++) {
                pthread_join(threads[j], NULL);
            }

            free(array);
            free(threads);
            free(threadData);

            return 1;
        }

        currentStart = threadData[i].endIndex;
    }

    for (int i = 0; i < threadCount; i++) {
        int status = pthread_join(threads[i], NULL);

        if (status != 0) {
            printf("Failed to join thread %d.\n", i);

            free(array);
            free(threads);
            free(threadData);

            return 1;
        }
    }

    long long finalSum = 0;

    printf("\nPartial results collected by parent:\n");

    for (int i = 0; i < threadCount; i++) {
        printf(
            "Thread %d partial sum = %lld\n",
            i,
            threadData[i].partialSum
        );

        finalSum += threadData[i].partialSum;
    }

    printf("\nFinal sum = %lld\n", finalSum);

    free(array);
    free(threads);
    free(threadData);

    return 0;
}