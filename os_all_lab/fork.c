#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct {
    int x;
    int y;

    // Used only to force a particular interleaving for demonstration.
    sem_t allow_p2_read;
    sem_t allow_p1_write;
    sem_t allow_p2_write;
} SharedData;

int main(void)
{
    setbuf(stdout, NULL);

    SharedData *data = mmap(
        NULL,
        sizeof(SharedData),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    if (data == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    data->x = 2;
    data->y = 3;

    // 1 means the semaphore is shared between processes.
    sem_init(&data->allow_p2_read, 1, 0);
    sem_init(&data->allow_p1_write, 1, 0);
    sem_init(&data->allow_p2_write, 1, 0);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        /*--------------- Process P2 ---------------*/

        // Wait until P1 has read the original values.
        sem_wait(&data->allow_p2_read);

        int old_x = data->x;
        int old_y = data->y;

        printf("P2 reads: x = %d, y = %d\n", old_x, old_y);

        // P2 has read the old values. Allow P1 to write.
        sem_post(&data->allow_p1_write);

        // Wait until P1 finishes writing.
        sem_wait(&data->allow_p2_write);

        /*
         * P2 calculates using the values it read earlier,
         * not the new values written by P1.
         */
        int new_x = old_x + 1;
        int new_y = new_x * old_y;

        data->x = new_x;
        data->y = new_y;

        printf("P2 writes using old values: x = %d, y = %d\n",
               data->x, data->y);

        _exit(0);
    }

    /*--------------- Process P1 ---------------*/

    int old_x = data->x;
    int old_y = data->y;

    printf("P1 reads: x = %d, y = %d\n", old_x, old_y);

    // Allow P2 to read the same original values.
    sem_post(&data->allow_p2_read);

    // Wait until P2 has completed its read.
    sem_wait(&data->allow_p1_write);

    data->x = old_x * old_y;
    data->y = old_y + 1;

    printf("P1 writes: x = %d, y = %d\n", data->x, data->y);

    // Allow P2 to overwrite P1's result.
    sem_post(&data->allow_p2_write);

    waitpid(pid, NULL, 0);

    printf("\nFinal shared values: x = %d, y = %d\n",
           data->x, data->y);

    printf("Correct serial result should be: x = 7, y = 28\n");

    sem_destroy(&data->allow_p2_read);
    sem_destroy(&data->allow_p1_write);
    sem_destroy(&data->allow_p2_write);

    munmap(data, sizeof(SharedData));

    return 0;
}