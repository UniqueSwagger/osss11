#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("paging_input.txt", "r", stdin);
    freopen("paging_output.txt", "w", stdout);
    int n, frames;
    cin >> n >> frames;

    vector<int> pages(n);

    for (int i = 0; i < n; i++)
        cin >> pages[i];

    queue<int> q;
    set<int> memory;

    int faults = 0;

    for (int page : pages) {
        if (memory.count(page))
            continue;

        faults++;

        if (memory.size() == frames) {
            int old = q.front();
            q.pop();
            memory.erase(old);
        }

        memory.insert(page);
        q.push(page);
    }

    cout << faults << '\n';
}