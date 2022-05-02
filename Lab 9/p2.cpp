#include <bits/stdc++.h>
using namespace std;

// If page found, updates the second chance bit to true
bool findPage(int x, int pages[], bool secondChance[], int f)
{
  for (int i = 0; i < f; i++)
  {
    if (pages[i] == x)
    {
      secondChance[i] = true;
      // Return true i.e. page would not be replaced
      return true;
    }
  }
  // Return false i.e. a page for replacement is selected
  return false;
}

// Updates the page in memory and returns the pointer
int replacePage(int x, int pages[], bool secondChance[], int f, int pointer)
{
  while (true)
  {
    if (!secondChance[pointer])
    {
      // Replace with new page and return updated pointer
      pages[pointer] = x;
      return (pointer + 1) % f;
    }
    secondChance[pointer] = false;
    // Pointer is updated in round robin manner
    pointer = (pointer + 1) % f;
  }
}

// Function for second chance page replacement algorithm
int sc(vector<int> pageOrder, int f)
{
  int pointer = 0, l = 0, pageFault = 0;
  int pages[f];
  memset(pages, -1, sizeof(pages));
  bool secondChance[f];
  for (int i = 0; i < pageOrder.size(); i++)
  {
    // Check if page in frame, if yes, updates the second chance bit to true
    if (!findPage(pageOrder[i], pages, secondChance, f))
    {
      // Selects and updates a victim page
      pointer = replacePage(pageOrder[i], pages, secondChance, f, pointer);
      pageFault++;
    }
  }
  return pageFault;
}

int main()
{
  int f, page;
  vector<int> pageOrder;
  cout << "\nFrame Count: ";
  cin >> f;
  cout << "Enter a page sequence (enter a character key to stop): \n";
  while (cin >> page)
    pageOrder.push_back(page);
  cout << "Second Chance Page Replacement Algorithm Used.\n";
  cout << "#Page Faults: " << sc(pageOrder, f) << "\n";
  return 0;
}