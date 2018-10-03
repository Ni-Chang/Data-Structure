#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders
{
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read()
  {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++)
    {
      cin >> key[i] >> left[i] >> right[i];
    }
  }
    
    vector<int> result_in_order;
    vector<int> result_pre_order;
    vector<int> result_post_order;

  void in_order(int t)
  {
    if(t!=-1)
    {
    	in_order(left[t]);
    	result_in_order.push_back(key[t]);
    	in_order(right[t]);
    }
  }

  void pre_order(int t)
  { 
   if(t!=-1)
   {
    result_pre_order.push_back(key[t]);
    pre_order(left[t]);
    pre_order(right[t]);
}
  }

  void post_order(int t)
  {
  	if(t!=-1)
  	{
    post_order(left[t]);
    post_order(right[t]);
    result_post_order.push_back(key[t]);
}
  }
};

void print(vector <int> a)
{
  for (size_t i = 0; i < a.size(); i++)
  {
    if (i > 0)
    {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space()
{
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  t.in_order(0);
  t.pre_order(0);
  t.post_order(0);
  print(t.result_in_order);
  print(t.result_pre_order);
  print(t.result_post_order);
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

