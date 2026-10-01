#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, frCnt;
  cin >> n >> frCnt;
  vector<int> ref(n);
  for (int i = 0; i < n; i++) {
    cin >> ref[i];
  }

  vector<int> frame(frCnt, -1);
  queue<int> q;
  int pg_flt = 0;
  for (int i = 0; i < n; i++) {
    cout << ref[i] << ": ";
    bool found = false;
    for (auto x : frame) {
      if (x == ref[i]) {
        found = true;
        break;
      }
    }
    if (!found) {
      pg_flt++;
      int cnt = 0;
      for (auto x : frame) {
        if (x >= 0) cnt++;
      }
      if (cnt < frCnt) {
        frame[cnt] = ref[i];
        q.push(ref[i]);
      } else {
        int gg = q.front();
        q.pop();
        q.push(ref[i]);
        for (auto& x : frame) {
          if (x == gg) {
            x = ref[i];
          }
        }
      }
    }
    for (auto x : frame) {
      if (x >= 0) cout << x << " ";
    }
    if (found) {
      cout << "Hit\n";
    } else
      cout << "Fault\n";
  }
  cout << "total page fault : " << pg_flt << "\n";
}