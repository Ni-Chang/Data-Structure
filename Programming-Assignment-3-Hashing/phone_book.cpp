#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

struct Query 
{
    string type, name;
    int number;
};

int m=1000;
vector<list<Query> > iList(m);
list<Query>:: iterator it;

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

int hash_function(int input)
{
	int a, b, p;
	a=34;
	b=2;
	p=10000019;
	return (a*input+b)%p%m;
}

void Add(Query input)
{
	bool isfind=false;
	for(it=iList[hash_function(input.number)].begin(); it!=iList[hash_function(input.number)].end(); ++it)
	{
		if(it->number==input.number)
		{
			it->name=input.name;
			isfind=true;
			break;
		}
	}
	if(!isfind)
		iList[hash_function(input.number)].push_back(input);
}

string Find(int num)
{
	for(it=iList[hash_function(num)].begin(); it!=iList[hash_function(num)].end(); ++it)
	{
		if(it->number==num)
		{
			return it->name;
		}
	}
	return "not found";
}
void Remove(int num)
{
	for(it=iList[hash_function(num)].begin(); it!=iList[hash_function(num)].end(); ++it)
	{
		if(it->number==num)
		{
			iList[hash_function(num)].erase(it);
			break;
		}
	}
}

vector<string> process_queries(const vector<Query>& queries)
{
    vector<string> result;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") 
        {
        	Add(queries[i]);
        }
        
        else if (queries[i].type == "del")
        {
        	Remove(queries[i].number);
        }
        
        else 
        {
        result.push_back(Find(queries[i].number));
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
