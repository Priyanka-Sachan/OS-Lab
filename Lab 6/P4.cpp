#include <bits/stdc++.h>

using namespace std;

class Process
{
public:
    int id;             // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int exitTime;       // Finish Time
    int waitingTime;    // Waiting Time
    int turnaroundTime; // Turn Around Time
    int remainingTime;  // Remaining Time
};

/* Comparator to sort according to arrival times */
bool byArrivalTime(Process p1, Process p2)
{
    if (p1.arrivalTime == p2.arrivalTime)
        return p1.id < p2.id;
    return p1.arrivalTime < p2.arrivalTime;
}

/* Comparator to sort according to exit times */
bool byExitTime(Process p1, Process p2)
{
    return p1.exitTime < p2.exitTime;
}

/* Operator overloading to sort according to burst times */
struct byRemainingTime
{
    bool operator()(Process *p1, Process *p2)
    {
        if (p1->remainingTime == p2->remainingTime)
            return p1->id > p2->id;
        return p1->remainingTime < p2->remainingTime;
    }
};

int main()
{
    int n, quantum = 1;
    cin >> n;
    vector<Process> processes;

    for (int i = 0; i < n; i++)
    {
        Process p;
        p.id = i + 1;
        cin >> p.arrivalTime >> p.burstTime;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    int queued = 0, currentTime = 0;
    // Sort vector according to arrival times
    sort(processes.begin(), processes.end(), byArrivalTime);
    priority_queue<Process *, vector<Process *>, byRemainingTime> globalQueue;

    // Find exitTime for all processes
    while (true)
    {
        // If all finished, break
        if (globalQueue.empty() && queued == n)
            break;

        // If queue is empty, increase currentTime
        if (globalQueue.empty())
            currentTime = max(currentTime, processes[queued].arrivalTime);

        // Push all processes whose arrival currentTime <= currentTime
        while (currentTime >= processes[queued].arrivalTime && queued < n)
        {
            globalQueue.push(&processes[queued]);
            queued++;
        }

        // Extract shortest remaining burst currentTime processes
        Process *p = globalQueue.top();
        globalQueue.pop();

        // Calculate waitingTime, exitTime, turnaroundTime, remainingTime (Update burstTime), LET
        currentTime += min(quantum, p->remainingTime);
        p->remainingTime -= min(quantum, p->remainingTime);
        if (p->remainingTime == 0)
        {
            p->exitTime = currentTime;
            p->turnaroundTime = p->exitTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;
        }
        else
            globalQueue.push(p);
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
}