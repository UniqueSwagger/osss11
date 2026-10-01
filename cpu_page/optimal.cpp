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
      } else {
        int willCng = -1;
        int far = -1;
        for (int j = 0; j < frCnt; j++) {
          int gg = frame[j];
          int next = -1;
          for (int k = i + 1; k < n; k++) {
            if (gg == ref[k]) {
              next = k;
              break;
            }
          }
          if (next == -1) {
            willCng = frame[j];
            break;
          }
          if (next > far) {
            far = next;
            willCng = frame[j];
          }
        }
        for (auto& x : frame) {
          if (x == willCng) {
            x = ref[i];
            break;
          }
        }
      }
    }
    for (auto x : frame) {
      if (x >= 0) cout << x << " ";
    }
    if (found) {
      cout << "hit\n";
    } else
      cout << "fault\n";
  }
  cout << "total page fault :" << pg_flt << "\n";
}