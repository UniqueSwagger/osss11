#include <bits/stdc++.h>
using namespace std;

struct Segment
{
    int start, end, process;
};

void printGantt(string name, vector<Segment> chart)
{
    cout << "\n"
         << name << ":\n";

    for (auto x : chart)
    {
        cout << x.start << " - " << x.end
             << " : P" << x.process + 1 << "\n";
    }
}

// FCFS
vector<Segment> FCFS(vector<int> burst)
{
    vector<Segment> chart;

    int time = 0;

    for (int i = 0; i < burst.size(); i++)
    {
        chart.push_back({time, time + burst[i], i});
        time += burst[i];
    }

    return chart;
}

// SJF Non-preemptive
vector<Segment> SJF(vector<int> burst)
{
    vector<Segment> chart;
    vector<pair<int, int>> processes;

    for (int i = 0; i < burst.size(); i++)
    {
        processes.push_back({burst[i], i});
    }

    sort(processes.begin(), processes.end());

    int time = 0;

    for (auto p : processes)
    {
        int bt = p.first;
        int id = p.second;

        chart.push_back({time, time + bt, id});
        time += bt;
    }

    return chart;
}

// Priority Non-preemptive
vector<Segment> PriorityScheduling(vector<int> burst, vector<int> priority)
{
    vector<Segment> chart;
    vector<pair<int, int>> processes;

    for (int i = 0; i < burst.size(); i++)
    {
        processes.push_back({priority[i], i});
    }

    // Smaller priority number = higher priority
    sort(processes.begin(), processes.end());

    int time = 0;

    for (auto p : processes)
    {
        int id = p.second;

        chart.push_back({time, time + burst[id], id});
        time += burst[id];
    }

    return chart;
}

// Round Robin
vector<Segment> RoundRobin(vector<int> burst, int quantum)
{
    vector<Segment> chart;

    int n = burst.size();
    vector<int> remaining = burst;

    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        q.push(i);
    }

    int time = 0;

    while (!q.empty())
    {
        int id = q.front();
        q.pop();

        int runTime = min(quantum, remaining[id]);

        chart.push_back({time,
                         time + runTime,
                         id});

        time += runTime;
        remaining[id] -= runTime;

        if (remaining[id] > 0)
        {
            q.push(id);
        }
    }

    return chart;
}
// Rate Monotonic Scheduling
vector<Segment> RMS(vector<int> period, vector<int> burst)
{
    int n = period.size();

    int limit = period[0];
    for (int i = 1; i < n; i++)
        limit = lcm(limit, period[i]);

    vector<int> remaining(n, 0);
    vector<Segment> chart;

    for (int time = 0; time < limit; time++)
    {

        // Release new jobs
        for (int i = 0; i < n; i++)
        {
            if (time % period[i] == 0)
                remaining[i] += burst[i];
        }

        // Find ready process with smallest period
        int id = -1;

        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                if (id == -1 || period[i] < period[id])
                    id = i;
            }
        }

        // Merge consecutive same-process execution
        if (!chart.empty() && chart.back().process == id)
        {
            chart.back().end++;
        }
        else
        {
            chart.push_back({time, time + 1, id});
        }

        if (id != -1)
            remaining[id]--;
    }

    return chart;
}
// Earliest Deadline First
vector<Segment> EDF(vector<int> period, vector<int> burst)
{
    int n = period.size();

    int limit = period[0];
    for (int i = 1; i < n; i++)
        limit = lcm(limit, period[i]);

    struct Job
    {
        int process;
        int remaining;
        int deadline;
    };

    vector<Job> jobs;
    vector<Segment> chart;

    for (int time = 0; time < limit; time++)
    {

        // Release new jobs
        for (int i = 0; i < n; i++)
        {
            if (time % period[i] == 0)
            {
                jobs.push_back({i,
                                burst[i],
                                time + period[i]});
            }
        }

        // Find unfinished job with earliest deadline
        int best = -1;

        for (int i = 0; i < jobs.size(); i++)
        {
            if (jobs[i].remaining > 0)
            {
                if (best == -1 ||
                    jobs[i].deadline < jobs[best].deadline)
                {
                    best = i;
                }
            }
        }

        int id = -1;

        if (best != -1)
            id = jobs[best].process;

        // Merge consecutive same-process execution
        if (!chart.empty() && chart.back().process == id)
        {
            chart.back().end++;
        }
        else
        {
            chart.push_back({time, time + 1, id});
        }

        if (best != -1)
            jobs[best].remaining--;
    }

    return chart;
}
int main()
{
    freopen("ingantt.txt", "r", stdin);
    freopen("outgantt.txt", "w", stdout);
    int n, quantum;
    cin >> n;

    vector<int> burst(n);
    vector<int> priority(n);

    for (int i = 0; i < n; i++)
    {
        cin >> burst[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> priority[i];
    }

    // int quantum = 3;
    cin >> quantum;
    int m;
    cin >> m;

    vector<int> period(m);
    vector<int> burstRT(m);

    for (int &x : period)
        cin >> x;

    for (int &x : burstRT)
        cin >> x;
    printGantt("FCFS", FCFS(burst));

    printGantt("SJF", SJF(burst));

    printGantt("Non-Preemptive Priority",
               PriorityScheduling(burst, priority));

    printGantt("Round Robin (q = 3)",
               RoundRobin(burst, quantum));

    printGantt("RMS", RMS(period, burstRT));
    printGantt("EDF", EDF(period, burstRT));

    return 0;
}