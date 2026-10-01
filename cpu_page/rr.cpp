#include <bits/stdc++.h>
using namespace std;
void rr(vector<int> bt, int qua) {
  int n = bt.size();

  int time = 0;

  vector<int> ct(n);
  vector<int> tat(n);
  vector<int> wt(n);

  queue<int> q;
  for (int i = 0; i < n; i++) {
    q.push(i);
  }
  vector<int> rem = bt;
  vector<int> order;
  while (!q.empty()) {
    int id = q.front();
    order.push_back(id + 1);
    q.pop();
    int run = min(rem[id], qua);
    time += run;
    rem[id] -= run;
    if (rem[id]) {
      q.push(id);
    } else {
      ct[id] = time;
    }
  }
  double avgwt = 0;
  for (int i = 0; i < n; i++) {
    tat[i] = ct[i];
    wt[i] = tat[i] - bt[i];
    avgwt += wt[i];
  }

  cout << "Execution order : \n";
  for (int i = 0; i < order.size(); i++) {
    cout << "P" << order[i];

    if (i != order.size() - 1) cout << " -> ";
  }
  cout << "\n";
  cout << "Process\tBt\tCt\tTat\tWt\n";
  for (int i = 0; i < n; i++) {
    cout << "p" << i + 1 << "\t\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i]
         << "\t" << wt[i] << "\n";
  }
  cout << "avg waiting time : " << (avgwt / n) << "\n";
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

  int q;
  cin >> q;
  rr(bt, q);
}