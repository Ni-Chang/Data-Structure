#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class JobQueue
{
 private:
  struct Node
  {
  	long long next_free_time;
  	int workers_number;
  };

  int num_workers_;
  vector<int> jobs_;
  vector<int> assigned_workers_;
  vector<long long> start_times_;
  vector <Node> worker;

  void WriteResponse() 
  const
  {
    for (int i = 0; i < jobs_.size(); ++i)
    {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData()
  {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
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

  void Find_next_free_worker(int job_time)
  {
  	int i=0;
  	int smallest;
  	worker[i].next_free_time+=job_time;
  	while(i<=num_workers_/2-1)
  	{
  		if(RightChild(i)<num_workers_ && (worker[LeftChild(i)].next_free_time > worker[RightChild(i)].next_free_time
  			|| (worker[LeftChild(i)].next_free_time==worker[RightChild(i)].next_free_time && worker[LeftChild(i)].workers_number > worker[RightChild(i)].workers_number)))
  			smallest=RightChild(i);
  		else
  			smallest=LeftChild(i);
  		if(worker[i].next_free_time < worker[smallest].next_free_time
  			|| (worker[i].next_free_time == worker[smallest].next_free_time && worker[i].workers_number < worker[smallest].workers_number))
  			return;
        else
        {
        	swap(worker[i], worker[smallest]);
        	i=smallest;
        }
    }

  }


  void AssignJobs()
  {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    worker.resize(num_workers_);
    for(int i=0; i<num_workers_; i++)
    {
    	worker[i].next_free_time=0;
    	worker[i].workers_number=i;
    }
    for (int i = 0; i < jobs_.size(); ++i)
    {
      assigned_workers_[i] = worker[0].workers_number;
      start_times_[i] = worker[0].next_free_time;
      Find_next_free_worker(jobs_[i]);
    }
  }


 public:
  void Solve()
  {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
