#include <bits/stdc++.h>

using namespace std;

// Total safe sequences
int total = 0;
// Class for a process and its resource requirement
class Process
{
public:
  int id;
  vector<int> alloc_res;
  vector<int> max_res;
  vector<int> req_res;
};

void enterVector(vector<int> &v, int n)
{
  for (int i = 0; i < n; i++)
  {
    int num;
    cin >> num;
    v.push_back(num);
  }
}

void displayVector(vector<int> v)
{
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << " ";
}

// Function to get all safe sequnces
void getAllSafeSequence(vector<Process> processes, vector<int> avail_res, vector<int> seq)
{
  // If no process left to execute
  if (processes.size() == 0)
  {
    cout << "P" << seq[0];
    for (int i = 1; i < seq.size(); i++)
      cout << "->P" << seq[i];
    cout << endl;
    total++;
  }

  vector<Process> up_processes;
  vector<int> up_avail_res, up_seq;
  for (int i = 0; i < processes.size(); i++)
  {
    // Check if required resources less than or equla to available resources
    const bool ok = equal(processes[i].req_res.begin(), processes[i].req_res.end(),
                          avail_res.begin(), avail_res.end(),
                          [](int a, int b) -> bool
                          { return a <= b; });
    // If yes, then execute that process
    if (ok)
    {
      up_processes = processes;
      up_avail_res = avail_res, up_seq = seq;

      // Empty used resources of the executed process
      for (int j = 0; j < processes.size(); j++)
        up_avail_res[j] += processes[i].alloc_res[j];
      up_processes.erase(up_processes.begin() + i);
      up_seq.push_back(processes[i].id);

      // Get next process to execute
      getAllSafeSequence(up_processes, up_avail_res, up_seq);
    }
  }
}

int main()
{
  int p, r;
  cout << "\nNumber of processes:";
  cin >> p;
  cout << "\nNumber of resources:";
  cin >> r;
  vector<Process> processes(p);
  vector<int> avail_res, seq;

  for (int i = 0; i < p; i++)
  {
    cout << "\nEnter resource (allocated & max) for process " << i << ":\n";
    processes[i].id = i;
    enterVector(processes[i].alloc_res, r);
    enterVector(processes[i].max_res, r);
    processes[i].req_res.resize(r);
    transform(processes[i].max_res.begin(), processes[i].max_res.end(),
              processes[i].alloc_res.begin(), processes[i].req_res.begin(), minus<int>());
  }
  cout << "\nEnter available resources:";
  enterVector(avail_res, r);

  cout << "\nAVAILABLE RESOURCES: ";
  displayVector(avail_res);
  cout << "\n";
  cout << "P | ALLOC_RES | MAX_RES | REQ_RES\n";
  for (int i = 0; i < p; i++)
  {
    cout << i << " | ";
    displayVector(processes[i].alloc_res);
    cout << " | ";
    displayVector(processes[i].max_res);
    cout << " | ";
    displayVector(processes[i].req_res);
    cout << "\n";
  }

  cout << "\nSAFE SEQUENCES\n";
  getAllSafeSequence(processes, avail_res, seq);
  if (total == 0)
    cout << "No safe sequence.";

  return 0;
}
