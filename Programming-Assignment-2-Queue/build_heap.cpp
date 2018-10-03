#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder 
{
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const 
  {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i)
    {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() 
  {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int Parent(int i)
  {
  	return (i-1)/2;
  }

  int LeftChild(int i)
  {
  	return 2*i+1;
  }

  int RightChild(int i)
  {
  	return 2*i+2;
  }

  void  MinHeapify(int i)
  {
  	int l=LeftChild(i);
    int r=RightChild(i);
    int smallest=i;
    if(l<data_.size() && data_[l]<data_[i])
      	smallest=l;
    else
      smallest=i;
    if(r<data_.size() && data_[r]<data_[smallest])
      	smallest=r;
    if(smallest!=i)
    {  	
    	swap(data_[smallest], data_[i]);
      	swaps_.push_back(make_pair(i, smallest));
      	MinHeapify(smallest);
      }
  }

  void GenerateSwaps() 
  {
    swaps_.clear();
    for (int i = data_.size()/2-1; i >= 0; --i)
      {
      	MinHeapify(i);
      }
      /*for (int j = i + 1; j < data_.size(); ++j) 
      {
        if (data_[i] > data_[j])
        {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }*/
  }

 public:
  void Solve() 
  {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
