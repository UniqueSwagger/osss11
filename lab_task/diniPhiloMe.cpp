#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int m;
  cin >> m;

  int room = 4;

  int chopstick[5] = {1, 1, 1, 1, 1};

  for (int k = 0; k < m; k++) {
    int id;
    cin >> id;

    // try to enter room
    if (room == 0) {
      cout << "Philosopher " << id << " is BLOCKED (Room Full)." << endl;
      continue;
    }

    room--;
    int left = id;
    int right = (id + 1) % 5;

    if (chopstick[left] == 0) {
      cout << "Philosopher " << id << " is BLOCKED (Waiting for Chopstick)."
           << endl;
      continue;
    }
    chopstick[left] = 0;

    if (chopstick[right] == 0) {
      cout << "Philosopher " << id << " is BLOCKED (Waiting for Chopstick)."
           << endl;
      continue;
    }

    chopstick[right] = 0;

    // Got both chopsticks
    cout << "Philosopher " << id << " is EATING." << endl;
  }
}