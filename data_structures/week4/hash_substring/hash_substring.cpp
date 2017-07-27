#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using std::string;
using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<long long>& output) {
    for (long long i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

long long PolyHash(const string& str, long long p, long long x){
    long long hash = 0;
    for (long long i = str.size()-1; i >= 0; --i)
        hash = ((hash * x + str[i]) % p + p) % p;
    return hash;
}

std::vector<long long> PrecomputeHashes(const Data& input, long long p, long long x){
    vector<long long> H(input.text.size() - input.pattern.size() + 1);
    string str = input.text.substr(input.text.size() - input.pattern.size(), input.pattern.size());
    H[input.text.size() - input.pattern.size()] = PolyHash(str,p,x);
    long long y = 1;
    for (long long i = 1; i <= input.pattern.size(); ++i)
        y = (y*x % p + p) % p;
    for (long long i = input.text.size() - input.pattern.size() - 1; i >= 0; --i)
        H[i] = ((x*H[i + 1] + input.text[i] - y * input.text[i + input.pattern.size()]) % p + p) % p;
    return H;
}

bool AreEqual(string s1, string s2){
    if (s1.size() != s2.size())
        return false;
    for (long long i = 0; i != s1.size(); ++i)
        if (s1[i] != s2[i])
            return false;
    return true;
}

std::vector<long long> get_occurrences2(const Data& input) {
    long long p = pow(10, 8)+1;
    long long x = rand() % (p - 1) + 1;
    long long pHash = PolyHash(input.pattern, p, x);
    vector<long long> results;
    vector<long long> H = PrecomputeHashes(input, p, x);
    for (long long i = 0; i <= input.text.size() - input.pattern.size(); ++i){
        if (pHash != H[i])
            continue;
        if(AreEqual(input.text.substr(i, input.pattern.size()), input.pattern))
            results.push_back(i);
    }
    return results;

}

std::vector<long long> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<long long> ans;
    for (long long i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences2(read_input()));
    return 0;
}
