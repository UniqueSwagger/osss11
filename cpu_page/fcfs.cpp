#include <bits/stdc++.h>
using namespace std;

void fcfs(vector<int> bt) {
  int n = bt.size();
  int time = 0;

  vector<int> ct(n);
  vector<int> tat(n);
  vector<int> wt(n);
  double tavt = 0;
  cout << "Execution Order: ";

  for (int i = 0; i < n; i++) {
    cout << "P" << i + 1;

    if (i != n - 1) cout << " -> ";
  }
  cout << "\n";
  for (int i = 0; i < n; i++) {
    time += bt[i];
    ct[i] = time;
    tat[i] = ct[i];
    wt[i] = tat[i] - bt[i];

    tavt += wt[i];
  }

  cout << "Process\tBt\tCt\tTat\tWt\n";
  for (int i = 0; i < n; i++) {
    cout << "p" << i + 1 << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i]
         << "\t" << wt[i] << "\n";
  }

  cout << "avg waiting time : " << (tavt / n) << "\n";
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n;
  cin >> n;

  vector<int> bt(n);

  for (int i = 0; i < n; i++) {
    cin >> bt[i];
  }

  fcfs(bt);
}