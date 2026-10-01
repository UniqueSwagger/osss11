#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;  // process , resource
  cin >> n >> m;

  vector<vector<int>> allocation(n, vector<int>(m));
  vector<vector<int>> maximum(n, vector<int>(m));
  vector<vector<int>> need(n, vector<int>(m));

  vector<int> ava(m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> allocation[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> maximum[i][j];
    }
  }

  for (int i = 0; i < m; ++i) {
    cin >> ava[i];
  }
  vector<int> work = ava;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = maximum[i][j] - allocation[i][j];
    }
  }

  vector<bool> finished(n, false);
  vector<int> safeSeq;

  while (safeSeq.size() < n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
      if (finished[i]) continue;

      bool possible = true;
      for (int j = 0; j < m; j++) {
        if (need[i][j] > work[j]) {
          possible = false;
          break;
        }
      }
      if (possible) {
        for (int j = 0; j < m; j++) {
          work[j] += allocation[i][j];
        }
        finished[i] = true;
        safeSeq.push_back(i);
        found = true;
      }
    }
    if (!found) {
      break;
    }
  }
}