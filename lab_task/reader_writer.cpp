#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int dataValue = 10;
int readCount = 0;

sem_t mutexLock;
sem_t writeLock;

void* reader(void* arg) {
  int id = *(int*)arg;

  sem_wait(&mutexLock);

  readCount++;

  if (readCount == 1) {
    sem_wait(&writeLock);
  }

  sem_post(&mutexLock);

  cout << "Reader " << id << " reads " << dataValue << endl;

  sem_wait(&mutexLock);

  readCount--;

  if (readCount == 0) {
    sem_post(&writeLock);
  }

  sem_post(&mutexLock);

  return NULL;
}

void* writer(void* arg) {
  sem_wait(&writeLock);

  dataValue++;

  cout << "Writer writes " << dataValue << endl;

  sem_post(&writeLock);

  return NULL;
}

int main() {
  sem_init(&mutexLock, 0, 1);
  sem_init(&writeLock, 0, 1);

  pthread_t r1, r2, w;

  int id1 = 1;
  int id2 = 2;

  pthread_create(&r1, NULL, reader, &id1);
  pthread_create(&r2, NULL, reader, &id2);
  pthread_create(&w, NULL, writer, NULL);

  pthread_join(r1, NULL);
  pthread_join(r2, NULL);
  pthread_join(w, NULL);

  return 0;
}