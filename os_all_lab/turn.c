#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* myturn(void* arg) {
    for(int i=0;i<8;++i) {
        sleep(1);
        printf("My turn! %d\n", i);
    }
    return NULL;
}

void yourturn() {
    for(int i=0;i<3;++i)
    {
        sleep(2);
        printf("Your turn! %d\n", i);
    }
}

int main() {
    pthread_t thread;

    pthread_create(&thread, NULL, myturn, NULL);
    // myturn();
    yourturn();
    pthread_join(thread, NULL);
}