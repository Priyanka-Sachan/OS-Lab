#include <bits/stdc++.h>

using namespace std;
class Process
{
public:
    int id;             // Process ID
    int priority;       // Process priority
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int exitTime;       // Finish Time
    int waitingTime;    // Waiting Time
    int turnaroundTime; // Turn Around Time
};

/* Comparator to sort according to exit times */
bool byExitTime(Process p1, Process p2)
{
    return p1.exitTime < p2.exitTime;
}

struct byPriority
{
    bool operator()(Process const &p1, Process const &p2) const
    {
        if (p1.priority != p2.priority)
            return p1.priority > p2.priority;
        else
            return p1.id > p2.id;
    }
};

int main()
{
    int n, currentTime = 0;
    vector<Process> processes;
    priority_queue<Process, vector<Process>, byPriority> globalQueue;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Process p;
        p.id = i + 1;
        cin >> p.arrivalTime >> p.burstTime >> p.priority;
        processes.push_back(p);
        globalQueue.push(p);
    }

    // Find exitTime for all processes
    while (!globalQueue.empty())
    {
        Process p = globalQueue.top();
        currentTime = max(currentTime, p.arrivalTime);
        currentTime += p.burstTime;
        processes[p.id - 1].exitTime = currentTime;
        globalQueue.pop();
    }

    // Calculate waitingTime and turnaroundTime for all processes
    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        processes[i].waitingTime = processes[i].exitTime - processes[i].arrivalTime - processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].exitTime - processes[i].arrivalTime;

        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    cout << fixed << setprecision(2) << avgWaitingTime << " " << avgTurnaroundTime << "\n";
    // Sort vector according to finish times
    sort(processes.begin(), processes.end(), byExitTime);
    for (int i = 0; i < n; i++)
        cout << "P" << processes[i].id << " ";

    return 0;
}