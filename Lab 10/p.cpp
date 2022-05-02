#include <bits/stdc++.h>

using namespace std;

// physical address space: 2^p
// virtual address space: 2^v
// frame size: 2^f
int p, v, f;
// Page table {page no., frame no.}
vector<vector<int>> page_table(0, vector<int>(2));
// Last page in memory;
int last_page = 0;
// Denotes availability of frames
vector<bool> frames_avail;

void display_page_table()
{
  cout << "\n | page | frame |";
  cout << "\n |------|-------|";
  for (int i = 0; i < page_table.size(); i++)
    cout << "\n | " << page_table[i][0] << " | " << page_table[i][1] << " | ";
}

vector<int> convert_to_binary(int num)
{
  vector<int> bin(v, 0);
  for (int i = 0; num != 0 && i < bin.size(); i++)
  {
    bin[i] = num % 2;
    num /= 2;
  }
  return bin;
}

int convert_to_decimal(vector<int> bin)
{
  int num = 0;
  for (int i = 0; i < bin.size(); i++)
    num += bin[i] * pow(2, i);
  return num;
}

void allocate(int process_size)
{
  cout << process_size << " bytes have allocated in frames : ";
  int frames_req = process_size / pow(2, f);
  for (int i = 0, j = 0; i < frames_avail.size() && j < frames_req; i++)
  {
    if (frames_avail[i])
    {
      vector<int> p(2);
      p[0] = last_page;
      p[1] = i;
      cout << i << " ";
      page_table.push_back(p);
      frames_avail[i] = false;
      j++;
      last_page++;
    }
  }
  display_page_table();
}

void translate(int logical_address)
{
  // Convert logical address into binary
  vector<int> bin = convert_to_binary(logical_address);
  vector<int> page_bin(v - f), offset(f);
  int page_no, frame_no, flag = 0;
  // Divide address into page no. & offset.
  for (int i = 0; i < bin.size(); i++)
  {
    if (i < f)
      offset[i] = bin[i];
    else
      page_bin[i - f] = bin[i];
  }
  // Get page no. in decimal format.
  page_no = convert_to_decimal(page_bin);
  // Find page no. in page table
  for (int i = 0; i < page_table.size(); i++)
  {
    // If page no. found in page table, save its frame else logical addreess invalid.
    if (page_table[i][0] == page_no)
    {
      frame_no = page_table[i][1];
      flag = 1;
      break;
    }
  }
  if (flag == 0)
    cout << "\nInvalid page address.";
  else
  {
    // Change the address with frame no.
    vector<int> frame_bin = convert_to_binary(frame_no);
    for (int i = 0; i < bin.size(); i++)
      if (i >= f)
        bin[i] = frame_bin[i - f];
    // Get the decimal format of physical address.
    cout << "\nPhysical address :" << convert_to_decimal(bin);
  }
}

void delete_page(int page_no)
{
  int flag = 0;
  // Find the page in the page table
  for (int i = 0; i < page_table.size(); i++)
  {
    // If found, remove it from page table
    // And change availability of frame
    if (page_table[i][0] == page_no)
    {
      frames_avail[page_table[i][1]] = true;
      page_table.erase(page_table.begin() + i);
      flag = 1;
      break;
    }
  }
  // If page not found, display an error, else show page table.
  if (flag == 0)
    cout << "\nInvalid page number.";
  else
    display_page_table();
}
int main()
{
  cout << "\nEnter p, v & f:";
  cin >> p >> v >> f;
  frames_avail = vector<bool>(pow(2, p - f), true);
  // Number of range of frames already occupied
  cout << "\nEnter Number of range of frames already occupied:";
  int n;
  cin >> n;
  cout << "\nEnter ranges:";
  for (int i = 0; i < n; i++)
  {
    int l, r;
    cin >> l >> r;
    for (int j = l; j <= r; j++)
    {
      // Occupy these frames
      frames_avail[j] = false;
    }
  }
  int q;
  cout << "\nEnter no. of queries:";
  cin >> q;
  char op;
  int num;
  while (q--)
  {
    cout << "\nEnter query: ";
    cin >> op >> num;
    if (op == 'a')
      allocate(num);
    else if (op == 't')
      translate(num);
    else if (op == 'd')
      delete_page(num);
    else
      cout << "\nWrong operation.";
  }
  return 0;
}