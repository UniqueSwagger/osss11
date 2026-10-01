#include <bits/stdc++.h>
using namespace std;

struct Task {
  int id;
  int execution;
  int period;
  int remaining;
  int deadline;
};

int main() {
  int n;
  cin >> n;

  vector<Task> task(n);

  for (int i = 0; i < n; i++) {
    task[i].id = i + 1;
    cin >> task[i].execution >> task[i].period;

    task[i].remaining = 0;
    task[i].deadline = 0;
  }

  int hyper = task[0].period;

  for (int i = 1; i < n; i++) {
    hyper = lcm(hyper, task[i].period);
  }

  for (int time = 0; time < hyper; time++) {
    // Release new jobs
    for (int i = 0; i < n; i++) {
      if (time % task[i].period == 0) {
        task[i].remaining += task[i].execution;

        task[i].deadline = time + task[i].period;
      }
    }

    int selected = -1;

    // Find ready task with earliest deadline
    for (int i = 0; i < n; i++) {
      if (task[i].remaining > 0) {
        if (selected == -1 || task[i].deadline < task[selected].deadline) {
          selected = i;
        }
      }
    }

    if (selected == -1) {
      cout << time << " - " << time + 1 << " : Idle" << endl;
    } else {
      cout << time << " - " << time + 1 << " : P" << task[selected].id << endl;

      task[selected].remaining--;
    }
  }

  return 0;
}