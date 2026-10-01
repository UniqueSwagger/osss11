#include <bits/stdc++.h>
using namespace std;
void sjf(vector<int> bt) {
  int n = bt.size();
  int time = 0;

  vector<int> ct(n);
  vector<int> tat(n);
  vector<int> wt(n);
  vector<int> order(n);

  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(),
       [&](auto a, auto b) { return bt[a] < bt[b]; });

  cout << "Execution order : \n";
  for (int i = 0; i < n; i++) {
    cout << "P" << order[i] + 1;

    if (i != n - 1) cout << " -> ";
  }
  cout << "\n";
  double tavt = 0;
  for (int i = 0; i < n; i++) {
    int id = order[i];
    time += bt[id];
    ct[id] = time;
    tat[id] = ct[id];
    wt[id] = tat[id] - bt[id];
    tavt += wt[id];
  }
  cout << "Process\tBt\tCt\tTat\tWt\n";
  for (int i = 0; i < n; i++) {
    cout << "p" << i + 1 << "\t\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i]
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
  sjf(bt);
}