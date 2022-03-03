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
    int currentCpuTime = 0;
    bool operator<(Process const &other) { return arrivalTime < other.arrivalTime; }
};

/* Comparator to sort according to exit times */
bool byExitTime(Process p1, Process p2)
{
    return p1.exitTime < p2.exitTime;
}

int main()
{
    int n, currentTime = 0;
    int quantum = 2;
    vector<Process> processes;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Process p;
        p.id = i + 1;
        cin >> p.arrivalTime >> p.burstTime;
        processes.push_back(p);
    }
    vector<Process> globalQueue = processes;
    sort(globalQueue.begin(), globalQueue.end());

    // Find exitTime for all processes
    for (int i = 0; !globalQueue.empty();)
    {
        // Process p = processes[globalQueue[i].id-1];
        if (processes[globalQueue[i].id - 1].arrivalTime > currentTime)
        {
            i++;
            if (i == globalQueue.size())
                i = 0;
            continue;
        }
        if (processes[globalQueue[i].id - 1].currentCpuTime + quantum >= processes[globalQueue[i].id - 1].burstTime)
        {
            currentTime += processes[globalQueue[i].id - 1].burstTime - processes[globalQueue[i].id - 1].currentCpuTime;
            processes[globalQueue[i].id - 1].currentCpuTime = processes[globalQueue[i].id - 1].burstTime;
            processes[globalQueue[i].id - 1].exitTime = currentTime;
            globalQueue.erase(globalQueue.begin() + i);
        }
        else
        {
            currentTime += quantum;
            processes[globalQueue[i].id - 1].currentCpuTime += quantum;
            i++;
        }
        if (i == globalQueue.size())
            i = 0;
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