#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

sem_t room;
sem_t chopstick[5];

void takeFork(int id) {
  if (sem_trywait(&room) != 0) {
    cout << "Philosopher " << id << " is BLOCKED (Room Full)." << endl;
    return;
  }

  if (sem_trywait(&chopstick[id]) != 0) {
    cout << "Philosopher " << id << " is BLOCKED (Waiting for Chopstick)."
         << endl;
    return;
  }

  int right = (id + 1) % 5;

  if (sem_trywait(&chopstick[right]) != 0) {
    cout << "Philosopher " << id << " is BLOCKED (Waiting for Chopstick)."
         << endl;
    return;
  }

  cout << "Philosopher " << id << " is EATING." << endl;
}

int main() {
  sem_init(&room, 0, 4);

  for (int i = 0; i < 5; i++) {
    sem_init(&chopstick[i], 0, 1);
  }

  int m;
  cin >> m;

  for (int i = 0; i < m; i++) {
    int id;
    cin >> id;

    takeFork(id);
  }

  return 0;
}