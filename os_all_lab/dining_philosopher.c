#include <stdio.h>
#include <semaphore.h>

sem_t room;
sem_t chopstick[5];

void initialize() {
    sem_init(&room, 0, 4);

    for (int i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);
}

void take_fork(int i) {
    if (sem_trywait(&room) != 0) {
        printf("Philosopher %d is BLOCKED (Room Full).\n", i);
        return;
    }

    if (sem_trywait(&chopstick[i]) != 0) {
        printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
        return;
    }

    if (sem_trywait(&chopstick[(i + 1) % 5]) != 0) {
        printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
        return;
    }

    printf("Philosopher %d is EATING.\n", i);
}

void destroy() {
    sem_destroy(&room);

    for (int i = 0; i < 5; i++)
        sem_destroy(&chopstick[i]);
}

int main() {
    int M, philosopher;

    initialize();

    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        scanf("%d", &philosopher);
        take_fork(philosopher);
    }

    destroy();

    return 0;
}