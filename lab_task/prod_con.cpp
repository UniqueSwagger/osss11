#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int buffer[5];
int in = 0;
int out = 0;

sem_t emptySlot;
sem_t fullSlot;
sem_t mutexLock;

void* producer(void* arg) {
  for (int item = 1; item <= 5; item++) {
    sem_wait(&emptySlot);
    sem_wait(&mutexLock);

    buffer[in] = item;

    cout << "Produced: " << item << endl;

    in = (in + 1) % 5;

    sem_post(&mutexLock);
    sem_post(&fullSlot);
  }

  return NULL;
}

void* consumer(void* arg) {
  for (int i = 1; i <= 5; i++) {
    sem_wait(&fullSlot);
    sem_wait(&mutexLock);

    int item = buffer[out];

    cout << "Consumed: " << item << endl;

    out = (out + 1) % 5;

    sem_post(&mutexLock);
    sem_post(&emptySlot);
  }

  return NULL;
}

int main() {
  sem_init(&emptySlot, 0, 5);
  sem_init(&fullSlot, 0, 0);
  sem_init(&mutexLock, 0, 1);

  pthread_t p, c;

  pthread_create(&p, NULL, producer, NULL);
  pthread_create(&c, NULL, consumer, NULL);

  pthread_join(p, NULL);
  pthread_join(c, NULL);

  return 0;
}