// 23 89 132 42 187
// 98 183 37 122 14 124 65 67
#include <bits/stdc++.h>
using namespace std;

void displayQueue(vector<vector<int>> sol)
{
  cout << "\n"
       << "(" << sol[0][1] << ")" << sol[0][0];
  for (int i = 1; i < sol.size(); i++)
    cout << " -> "
         << "(" << sol[i][1] << ")" << sol[i][0];
}

void saveQueue(string method, vector<vector<int>> sol, int head)
{
  fstream outfile;
  method += ".dat";
  outfile.open(method, fstream::out | fstream::trunc);
  outfile.precision(6);
  outfile << fixed << head << "   " << fixed << 0 << endl;
  for (int i = 0; i < sol.size(); i++)
  {
    outfile << fixed << sol[i][0] << "   " << fixed << sol[i][1] << endl;
  }
  outfile.close();
}

vector<vector<int>> fcfs(vector<int> queue, int head)
{
  vector<vector<int>> sol(queue.size(), vector<int>(2));
  int hm = 0;
  for (int i = 0; i < queue.size(); i++)
  {
    hm += abs(head - queue[i]);
    head = queue[i];
    sol[i][0] = queue[i];
    sol[i][1] = hm;
  }
  cout << "\n Seek time: " << hm * 5 << " ms";
  return sol;
}

vector<vector<int>> scan(vector<int> queue, int head)
{
  vector<vector<int>> sol(0, vector<int>(2));
  int hm = 0;
  char direction = 'l';

  vector<int> left, right;

  for (int i = 0; i < queue.size(); i++)
  {
    if (queue[i] <= head)
      left.push_back(queue[i]);
    if (queue[i] > head)
      right.push_back(queue[i]);
  }

  left.push_back(0);
  right.push_back(199);

  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int run = 2;
  while (run--)
  {
    if (direction == 'l')
    {
      for (int i = left.size() - 1; i >= 0; i--)
      {
        hm += abs(left[i] - head);
        head = left[i];
        vector<int> temp(2);
        temp[0] = left[i];
        temp[1] = hm;
        sol.push_back(temp);
      }
      direction = 'r';
    }
    else if (direction == 'r')
    {
      for (int i = 0; i < right.size(); i++)
      {
        hm += abs(right[i] - head);
        head = right[i];
        vector<int> temp(2);
        temp[0] = right[i];
        temp[1] = hm;
        sol.push_back(temp);
      }
      direction = 'l';
    }
  }

  cout << "\n Seek time: " << hm * 5 << " ms";
  return sol;
}

vector<vector<int>> cScan(vector<int> queue, int head)
{
  vector<vector<int>> sol(0, vector<int>(2));
  int hm = 0;
  char direction = 'l';

  vector<int> left, right;

  for (int i = 0; i < queue.size(); i++)
  {
    if (queue[i] <= head)
      left.push_back(queue[i]);
    if (queue[i] > head)
      right.push_back(queue[i]);
  }

  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int run = 2;
  while (run--)
  {
    if (direction == 'l')
    {
      for (int i = left.size() - 1; i >= 0; i--)
      {
        hm += abs(left[i] - head);
        head = left[i];
        vector<int> temp(2);
        temp[0] = left[i];
        temp[1] = hm;
        sol.push_back(temp);
      }
      direction = 'r';
    }
    else if (direction == 'r')
    {
      for (int i = 0; i < right.size(); i++)
      {
        hm += abs(right[i] - head);
        head = right[i];
        vector<int> temp(2);
        temp[0] = right[i];
        temp[1] = hm;
        sol.push_back(temp);
      }
      direction = 'l';
    }
  }

  cout << "\n Seek time: " << hm * 5 << " ms";
  return sol;
}

vector<vector<int>> sstf(vector<int> queue, int head)
{
  vector<vector<int>> sol(queue.size(), vector<int>(2));
  int hm = 0;
  for (int i = 0; i < sol.size(); i++)
  {
    int min = INT_MAX, id;
    for (int j = 0; j < queue.size(); j++)
    {
      if (abs(head - queue[j]) < min)
      {
        min = abs(head - queue[j]);
        id = j;
      }
    }
    hm += abs(head - queue[id]);
    head = queue[id];
    sol[i][0] = queue[id];
    sol[i][1] = hm;
    queue.erase(queue.begin() + id);
  }
  cout << "\n Seek time: " << hm * 5 << " ms";
  return sol;
}

int main()
{
  int head = 100;
  int n;
  cin >> n;
  vector<int> queue(n);
  for (int i = 0; i < n; i++)
    cin >> queue[i];

  cout << "\nFCFS";
  vector<vector<int>> fcfs_sol = fcfs(queue, head);
  displayQueue(fcfs_sol);
  saveQueue("fcfs", fcfs_sol, head);

  cout << "\nSCAN";
  vector<vector<int>> scan_sol = scan(queue, head);
  displayQueue(scan_sol);
  saveQueue("scan", scan_sol, head);

  cout << "\nC-SCAN";
  vector<vector<int>> cscan_sol = cScan(queue, head);
  displayQueue(cscan_sol);
  saveQueue("c-scan", cscan_sol, head);

  cout << "\nSSTF";
  vector<vector<int>> sstf_sol = sstf(queue, head);
  displayQueue(sstf_sol);
  saveQueue("sstf", sstf_sol, head);

  return 0;
}