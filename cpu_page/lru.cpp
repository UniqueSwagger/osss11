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
  int pg_flt = 0;

  vector<int> frame(frCnt, -1);
  vector<int> lastUsed(frCnt, -1);

  for (int i = 0; i < n; i++) {
    cout << ref[i] << " : ";
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
        lastUsed[cnt] = i;
      } else {
        int least = *min_element(lastUsed.begin(), lastUsed.end());
        for (auto& x : frame) {
          if (x == ref[least]) {
            x = ref[i];
          }
        }
        for (auto& x : lastUsed) {
          if (x == least) {
            x = i;
          }
        }
      }
    } else {
      int pos = -1;
      for (int j = 0; j < frCnt; j++) {
        if (frame[j] == ref[i]) {
          pos = j;
          break;
        }
      }
      lastUsed[pos] = i;
      // hit er jonnow last used update kora lagbe
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