#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long ull;

struct Data 
{
    string pattern, text;
};

Data read_input() 
{
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output)
{
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull PolyHash(string S, int p, int x)
{
    ull hash=0;
    for(int i=S.size()-1; i>=0; i--)
    {
        hash=(hash*x+S[i])%p;
    }
    return hash;
}

vector<ull> PrecomputeHashes(string T, int P_len, int p, int x)
{
    vector<ull>H(T.size()-P_len+1);
    string S=T.substr(T.size()-P_len, P_len);
    H[T.size()-P_len]=PolyHash(S, p, x);
    int y=1;
    for(int i=1; i<=P_len; i++)
    {
        y=(y*x)%p;
    }
    for(int i=(T.size()-P_len-1); i>=0; i--)
    {
        H[i]=(x*H[i+1]+T[i]-y*T[i+P_len])%p;
    }
    return H;
}

vector<int> RabinKarp(string T, string P)
{
    int p=10000019;
    int x=2;
    bool AreEqual;
    vector <int> result;
    int pHash=PolyHash(P, p, x);
    vector<ull> H=PrecomputeHashes(T, P.size(), p, x);
    for(int i=0; i<=T.size()-P.size(); i++)
    {
        if(pHash!=H[i])
            continue;
        AreEqual=true;
        for(int j=0; j<P.size(); j++)
        {
            if(T[i+j]!=P[j])
            {
                AreEqual=false;
                break;
            }
        }
        if (AreEqual)
            result.push_back(i);
    }
    return result;
}

std::vector<int> get_occurrences(const Data& input)
{
    const string& s = input.pattern, t = input.text;
    vector<int> ans=RabinKarp(t, s);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
