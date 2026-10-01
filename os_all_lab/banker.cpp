#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("banker_input_unsafe.txt","r",stdin);
    freopen("banker_output.txt","w",stdout);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> mx(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mx[i][j];

    for (int j = 0; j < m; j++)
        cin >> available[j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = mx[i][j] - allocation[i][j];

    vector<int> work = available;
    vector<bool> finish(n, false);
    vector<int> safeSequence;

    while (safeSequence.size() < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (finish[i]) continue;

            bool possible = true;

            for (int j = 0; j < m; j++) {
                if (need[i][j] > work[j]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                for (int j = 0; j < m; j++)
                    work[j] += allocation[i][j];

                finish[i] = true;
                safeSequence.push_back(i);
                found = true;
            }
        }

        if (!found) break;
    }

    if (safeSequence.size() == n) {
        cout << "Safe\n";

        for (int x : safeSequence)
            cout << "P" << x << " ";

        cout << '\n';
    } else {
        cout << "Unsafe\n";

        for (int i = 0; i < n; i++)
            if (!finish[i])
                cout << "P" << i << " ";

        cout << '\n';
    }
}