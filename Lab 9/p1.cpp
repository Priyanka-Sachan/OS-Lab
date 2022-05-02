#include <bits/stdc++.h>

using namespace std;

// Structure for a page
struct Page
{
  int id;
  int position = -1;
  int insertTime = -1;
  int lastTime = -1;
};

/* Comparator for FIFO Set */
struct fifo_page_comparator
{
  bool operator()(Page *p1, Page *p2) const
  {
    return p1->insertTime < p2->insertTime;
  }
};

// Function to update a page's properties if in frame
void updatePage(Page *page, int insertTime, int position, int lastTime)
{
  if (insertTime != -1)
    page->insertTime = insertTime;
  if (position != -1)
    page->position = position;
  page->lastTime = lastTime;
  return;
}

// Function for FIFO page replacement
int fifo(int f, vector<int> pageOrder, vector<vector<int>> *frameTimeline)
{
  vector<int> frames;
  set<Page *, fifo_page_comparator> S;
  int time = 0, pageFaults = 0;
  Page pages[99];
  for (int i = 0; i < 99; i++)
    pages[i].id = i + 1;

  (*frameTimeline).push_back(frames);
  for (int i = 0; i < pageOrder.size(); i++)
  {
    time++;
    Page *page = &pages[pageOrder[i] - 1];
    // If page not in the current frames
    if (S.find(page) == S.end())
    {
      pageFaults++;
      // If empty frames available
      if (S.size() < f)
      {
        updatePage(page, time, frames.size(), time);
        // Insert into next frames
        frames.push_back(page->id);
        S.insert(page);
      }
      // If all frames already occupied
      else
      {
        updatePage(page, time, (*S.begin())->position, time);
        // Replace first inserted frames with current frames
        frames[page->position] = page->id;
        S.erase(S.begin());
        S.insert(page);
      }
    }
    // If page found in current frames,update last time
    else
      updatePage(page, -1, -1, time);
    (*frameTimeline).push_back(frames);
  }

  return pageFaults;
}

// Function for LRU page replacement
int lru(int f, vector<int> pageOrder, vector<vector<int>> *frameTimeline)
{
  vector<int> frames;
  list<Page *> S;
  int time = 0, pageFaults = 0;
  Page pages[99];
  for (int i = 0; i < 99; i++)
    pages[i].id = i + 1;

  (*frameTimeline).push_back(frames);
  for (int i = 0; i < pageOrder.size(); i++)
  {
    time++;
    Page *page = &pages[pageOrder[i] - 1];
    // If page not in the current frames
    if (find(S.begin(), S.end(), page) == S.end())
    {
      pageFaults++;
      // If empty frames available
      if (S.size() < f)
      {
        updatePage(page, time, frames.size(), time);
        // Insert into next frames
        frames.push_back(page->id);
        S.push_back(page);
      }
      // If all frames are already occupied
      else
      {
        updatePage(page, time, (*S.begin())->position, time);
        // Replace least recently used frames with current frames
        frames[page->position] = page->id;
        S.pop_front();
        S.push_back(page);
      }
    }
    // If page found in current frames, update last time and make changes to list
    else
    {
      S.erase(find(S.begin(), S.end(), page));
      S.push_back(page);
      updatePage(page, -1, -1, time);
    }
    (*frameTimeline).push_back(frames);
  }

  return pageFaults;
}

// Function for Optimal page replacement
int optimal(int f, vector<int> pageOrder, vector<vector<int>> *frameTimeline)
{
  vector<int> frames;
  int time = 0, pageFaults = 0;

  (*frameTimeline).push_back(frames);
  for (int i = 0; i < pageOrder.size(); i++)
  {
    time++;
    // If page is not in the current frames
    if (find(frames.begin(), frames.end(), pageOrder[i]) == frames.end())
    {
      pageFaults++;
      // If frames filled are less than max frames available
      // Insert into next frames
      if (frames.size() < f)
        frames.push_back(pageOrder[i]);
      // If all frames are already occupied
      else
      {
        // Find the page that will be out of use the longest
        int idx = 0;
        int longest_wait = 0;
        for (int j = 0; j < frames.size(); j++)
        {
          int wait = INT_MAX;
          for (int k = i + 1; k < pageOrder.size(); k++)
            if (pageOrder[k] == frames[j])
            {
              wait = k - i;
              break;
            }
          if (wait > longest_wait)
          {
            longest_wait = wait;
            idx = j;
          }
        }
        // Replace the page unneeded the longest by current page
        frames[idx] = pageOrder[i];
      }
    }
    // Do nothing and proceed to printing frames if page is in current frames
    (*frameTimeline).push_back(frames);
  }
  return pageFaults;
}

/* Function to print frames contents at any instant of time */
void printFrames(vector<int> frames, int f, int time)
{
  for (int i = 0; i < f; i++)
    if (i < frames.size())
      cout << frames[i] << "\t";
    else
      cout << "X\t";
  cout << "at t = " << time << endl;
}

int main()
{
  int f, page;
  vector<int> pageOrder;
  cout << "\nFrame Count: ";
  cin >> f;
  vector<vector<int>> FIFOframeTimeline(0, vector<int>(f)),
      LRUframeTimeline(0, vector<int>(f + 1)),
      OPTframeTimeline(0, vector<int>(f + 1));
  int FIFOpageFaults, LRUpageFaults, OPTpageFaults, bestPageFault;
  cout << "Enter a page sequence (enter a character key to stop): \n";
  while (cin >> page)
    pageOrder.push_back(page);

  FIFOpageFaults = fifo(f, pageOrder, &FIFOframeTimeline);
  LRUpageFaults = lru(f, pageOrder, &LRUframeTimeline);
  OPTpageFaults = optimal(f, pageOrder, &OPTframeTimeline);

  string bestAlgo;
  vector<vector<int>> bestFrameTimeline(0, vector<int>(f));
  if (FIFOpageFaults < LRUpageFaults && FIFOpageFaults < OPTpageFaults)
  {
    bestAlgo = "FIFO";
    bestPageFault = FIFOpageFaults;
    bestFrameTimeline = FIFOframeTimeline;
  }
  else if (LRUpageFaults < FIFOpageFaults && LRUpageFaults < OPTpageFaults)
  {
    bestAlgo = "LRU";
    bestPageFault = LRUpageFaults;
    bestFrameTimeline = LRUframeTimeline;
  }
  else
  {
    bestAlgo = "OPTIMAL";
    bestPageFault = OPTpageFaults;
    bestFrameTimeline = OPTframeTimeline;
  }
  cout << "Best Page Replacement Algorithms: " << bestAlgo << "\n\n";
  for (int i = 0; i < f; i++)
    cout << "F" << i + 1 << "\t";
  cout << endl;
  for (int i = 0; i < bestFrameTimeline.size(); i++)
    printFrames(bestFrameTimeline[i], f, i);
  cout << "#Page Faults: " << bestPageFault << "\n";
}