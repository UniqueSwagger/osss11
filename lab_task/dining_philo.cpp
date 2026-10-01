#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int m;
  cin >> m;

  int room = 4;

  // 1 = free, 0 = occupied
  int chopstick[5] = {1, 1, 1, 1, 1};

  for (int k = 0; k < m; k++) {
    int id;
    cin >> id;

    // First: try to enter the room
    if (room == 0) {
      cout << "Philosopher " << id << " is BLOCKED (Room Full)." << endl;
      continue;
    }

    room--;

    int left = id;
    int right = (id + 1) % 5;

    // Try to take left chopstick
    if (chopstick[left] == 0) {
      cout << "Philosopher " << id << " is BLOCKED (Waiting for Chopstick)."
           << endl;
      continue;
    }

    chopstick[left] = 0;

    // Try to take right chopstick
    if (chopstick[right] == 0) {
      cout << "Philosopher " << id << " is BLOCKED (Waiting for Chopstick)."
           << endl;
      continue;
    }

    chopstick[right] = 0;

    // Got both chopsticks
    cout << "Philosopher " << id << " is EATING." << endl;
  }

  return 0;
}
