// Author: Shohidur Rahman
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

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = maximum[i][j] - allocation[i][j];
    }
  }

  vector<bool> finished(n, false);
  vector<int> safeSequence;

  vector<int> work = ava;

  while (safeSequence.size() < n) {
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
        safeSequence.push_back(i);

        found = true;
      }
    }

    if (!found) break;
  }

  cout << "\nNeed Matrix:\n";

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << need[i][j] << " ";
    }
    cout << endl;
  }

  if (safeSequence.size() == n) {
    cout << "\nSystem is in SAFE state.\n";

    cout << "Safe Sequence: ";

    for (int i = 0; i < n; i++) {
      cout << "P" << safeSequence[i];

      if (i != n - 1) cout << " -> ";
    }

    cout << endl;
  } else {
    cout << "\nSystem is in UNSAFE state.\n";
    cout << "Sequence till now is : \n";
    for (int i = 0; i < safeSequence.size(); i++) {
      cout << "P" << safeSequence[i];

      if (i != n - 1) cout << " -> ";
    }

    cout << " Stuck\n";
    cout << endl;
  }

  return 0;
}

// 5 3

// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3

// 3 3 2
