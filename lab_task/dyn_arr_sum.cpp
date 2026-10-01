#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

vector<int> arr;

struct Data {
  int start;
  int end;
  int sum;
};

void* calculateSum(void* arg) {
  Data* d = (Data*)arg;

  d->sum = 0;

  for (int i = d->start; i < d->end; i++) {
    d->sum += arr[i];
  }

  return NULL;
}

int main() {
  int n, threadCount;

  cout << "Enter number of elements: ";
  cin >> n;

  arr.resize(n);

  cout << "Enter elements: ";

  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  cout << "Enter number of threads: ";
  cin >> threadCount;

  vector<pthread_t> threads(threadCount);
  vector<Data> data(threadCount);

  int part = n / threadCount;

  for (int i = 0; i < threadCount; i++) {
    data[i].start = i * part;

    if (i == threadCount - 1)
      data[i].end = n;
    else
      data[i].end = (i + 1) * part;

    pthread_create(&threads[i], NULL, calculateSum, &data[i]);
  }

  int total = 0;

  for (int i = 0; i < threadCount; i++) {
    pthread_join(threads[i], NULL);

    total += data[i].sum;
  }

  cout << "Total Sum = " << total << endl;

  return 0;
}