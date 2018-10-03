#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor 
{
    int bucket_count;
    vector<list<string> > iList;
    list<string>::iterator it;
    list<string>::reverse_iterator r_it;
    size_t hash_func(const string& s) const 
    {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const 
    {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void Add(string input)
    {
        for(it=iList[hash_func(input)].begin();it!=iList[hash_func(input)].end();it++)
        {
            if(*it==input)
                return;
        }
        iList[hash_func(input)].push_back(input);
    }

    void Del(string input)
    {
        for(it=iList[hash_func(input)].begin();it!=iList[hash_func(input)].end();it++)
        {
            if(*it==input)
            {
                iList[hash_func(input)].erase(it);
                break;
            }
        }
    }

    string Find(string input)
    {
        for(it=iList[hash_func(input)].begin();it!=iList[hash_func(input)].end();it++)
        {
            if(*it==input)
                return "yes";
        }
        return "no";
    }

    void Check(int input)
    {
        for(r_it=iList[input].rbegin();r_it!=iList[input].rend();r_it++)
            cout<<*r_it <<" ";
    }

    void processQuery(const Query& query)
    {
        iList.resize(bucket_count);
        if (query.type == "check") 
        {
            Check(query.ind);
            cout << "\n";
        } 
        else if (query.type == "find")
        {
            cout<<Find(query.s)<<"\n";
        }
        else if (query.type == "add") 
            Add(query.s);
        else if (query.type == "del")
            Del(query.s);
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
