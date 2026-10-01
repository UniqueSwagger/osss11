#include <bits/stdc++.h>
using namespace std;

struct Segment {
  int start, end;
  string name;
};

void addSegment(vector<Segment>& g, int start, int end, string name) {
  if (start == end) return;

  if (!g.empty() && g.back().name == name && g.back().end == start)
    g.back().end = end;
  else
    g.push_back({start, end, name});
}

void printGantt(string title, vector<Segment>& g) {
  cout << "\n" << title << "\n";

  if (g.empty()) {
    cout << "No segments\n";
    return;
  }

  cout << g[0].start;

  for (auto s : g) cout << " --" << s.name << "-- " << s.end;

  cout << "\n";
}

void printTimes(vector<int>& bt, vector<int>& ct) {
  int n = bt.size();
  double avgWT = 0;

  cout << "Process\tTAT\tWT\n";

  for (int i = 0; i < n; i++) {
    int tat = ct[i];
    int wt = tat - bt[i];

    cout << "P" << i + 1 << "\t\t" << tat << "\t" << wt << "\n";

    avgWT += wt;
  }

  cout << "Average WT = " << fixed << setprecision(2) << avgWT / n << "\n";
}

double FCFS(vector<int> bt) {
  int n = bt.size();
  int time = 0;

  vector<int> ct(n);
  vector<Segment> g;

  for (int i = 0; i < n; i++) {
    addSegment(g, time, time + bt[i], "P" + to_string(i + 1));

    time += bt[i];
    ct[i] = time;
  }

  printGantt("FCFS", g);
  printTimes(bt, ct);

  double avg = 0;

  for (int i = 0; i < n; i++) avg += ct[i] - bt[i];

  return avg / n;
}

double SJF(vector<int> bt) {
  int n = bt.size();
  int time = 0;

  vector<int> order(n);
  vector<int> ct(n);

  iota(order.begin(), order.end(), 0);

  stable_sort(order.begin(), order.end(),
              [&](int a, int b) { return bt[a] < bt[b]; });

  vector<Segment> g;

  for (int id : order) {
    addSegment(g, time, time + bt[id], "P" + to_string(id + 1));

    time += bt[id];
    ct[id] = time;
  }

  printGantt("SJF", g);
  printTimes(bt, ct);

  double avg = 0;

  for (int i = 0; i < n; i++) avg += ct[i] - bt[i];

  return avg / n;
}

double PriorityNonPreemptive(vector<int> bt, vector<int> priority) {
  int n = bt.size();
  int time = 0;

  vector<int> order(n);
  vector<int> ct(n);

  iota(order.begin(), order.end(), 0);

  stable_sort(order.begin(), order.end(),
              [&](int a, int b) { return priority[a] > priority[b]; });

  vector<Segment> g;

  for (int id : order) {
    addSegment(g, time, time + bt[id], "P" + to_string(id + 1));

    time += bt[id];
    ct[id] = time;
  }

  printGantt("Non-preemptive Priority", g);
  printTimes(bt, ct);

  double avg = 0;

  for (int i = 0; i < n; i++) avg += ct[i] - bt[i];

  return avg / n;
}

double RoundRobin(vector<int> bt, int quantum) {
  int n = bt.size();
  int time = 0;

  vector<int> remaining = bt;
  vector<int> ct(n);

  queue<int> q;

  for (int i = 0; i < n; i++) q.push(i);

  vector<Segment> g;

  while (!q.empty()) {
    int id = q.front();
    q.pop();

    int run = min(quantum, remaining[id]);

    addSegment(g, time, time + run, "P" + to_string(id + 1));

    time += run;
    remaining[id] -= run;

    if (remaining[id] > 0)
      q.push(id);
    else
      ct[id] = time;
  }

  printGantt("Round Robin", g);
  printTimes(bt, ct);

  double avg = 0;

  for (int i = 0; i < n; i++) avg += ct[i] - bt[i];

  return avg / n;
}

struct Job {
  int process;
  int release;
  int deadline;
  int remaining;
};

int getHyperPeriod(vector<int>& period) {
  int h = period[0];

  for (int x : period) h = lcm(h, x);

  return h;
}

void RMS(vector<int> period, vector<int> execution) {
  int n = period.size();
  int H = getHyperPeriod(period);

  vector<Job> jobs;
  vector<Segment> g;

  bool missed = false;

  for (int time = 0; time < H; time++) {
    for (auto& job : jobs) {
      if (job.deadline == time && job.remaining > 0) {
        cout << "\nP" << job.process + 1 << " missed deadline at " << time
             << "\n";

        missed = true;
      }
    }
    if (missed) break;
    for (int i = 0; i < n; i++) {
      if (time % period[i] == 0) {
        jobs.push_back({i, time, time + period[i], execution[i]});
      }
    }

    int best = -1;

    for (int i = 0; i < jobs.size(); i++) {
      if (jobs[i].remaining == 0) continue;

      if (best == -1 || period[jobs[i].process] < period[jobs[best].process] ||

          (period[jobs[i].process] == period[jobs[best].process] &&
           jobs[i].release < jobs[best].release)) {
        best = i;
      }
    }

    if (best == -1) {
      addSegment(g, time, time + 1, "Idle");
    }

    else {
      addSegment(g, time, time + 1, "P" + to_string(jobs[best].process + 1));

      jobs[best].remaining--;
    }
  }

  printGantt("Rate Monotonic Scheduling", g);

  if (missed)
    cout << "RMS: NOT schedulable\n";
  else
    cout << "RMS: Schedulable\n";
}

void EDF(vector<int> period, vector<int> execution) {
  int n = period.size();
  int H = getHyperPeriod(period);

  vector<Job> jobs;
  vector<Segment> g;

  bool missed = false;

  for (int time = 0; time < H; time++) {
    for (auto& job : jobs) {
      if (job.deadline == time && job.remaining > 0) {
        cout << "\nP" << job.process + 1 << " missed deadline at " << time
             << "\n";

        missed = true;
      }
    }

    for (int i = 0; i < n; i++) {
      if (time % period[i] == 0) {
        jobs.push_back({i, time, time + period[i], execution[i]});
      }
    }

    int best = -1;

    for (int i = 0; i < jobs.size(); i++) {
      if (jobs[i].remaining == 0) continue;

      if (best == -1 ||

          jobs[i].deadline < jobs[best].deadline ||

          (jobs[i].deadline == jobs[best].deadline &&
           jobs[i].release < jobs[best].release)) {
        best = i;
      }
    }

    if (best == -1) {
      addSegment(g, time, time + 1, "Idle");
    }

    else {
      addSegment(g, time, time + 1, "P" + to_string(jobs[best].process + 1));

      jobs[best].remaining--;
    }
  }

  printGantt("Earliest Deadline First", g);

  if (missed)
    cout << "EDF: NOT schedulable\n";
  else
    cout << "EDF: Schedulable\n";
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  cin >> n;

  vector<int> burst(n);
  vector<int> priority(n);

  for (int& x : burst) cin >> x;

  for (int& x : priority) cin >> x;

  int quantum;
  cin >> quantum;

  double fcfsAvg = FCFS(burst);

  double sjfAvg = SJF(burst);

  double priorityAvg = PriorityNonPreemptive(burst, priority);

  double rrAvg = RoundRobin(burst, quantum);

  vector<pair<double, string>> avg = {

      {fcfsAvg, "FCFS"},
      {sjfAvg, "SJF"},
      {priorityAvg, "Priority"},
      {rrAvg, "Round Robin"}};

  auto best = min_element(avg.begin(), avg.end());

  cout << "\nMinimum Average Waiting Time: " << best->second << " = " << fixed
       << setprecision(2) << best->first << "\n";

  int m;
  cin >> m;

  vector<int> period(m);
  vector<int> execution(m);

  for (int& x : period) cin >> x;

  for (int& x : execution) cin >> x;

  RMS(period, execution);

  EDF(period, execution);

  return 0;
}