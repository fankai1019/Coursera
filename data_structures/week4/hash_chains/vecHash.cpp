#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <utility>

using std::string;
using namespace std;



struct Query {
	string type, s;
	size_t ind;
};

//struct pairs{
//	Query query;
//	int hashvalue;
//};

class QueryProcessor {
	int bucket_count;
	//hash table implementation
	vector<list<string>> hash_table;
	typedef list<string>::iterator it;
	size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {hash_table.resize(bucket_count); }

	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}


	void processQuery(const Query& query){
		if (query.type == "add"){
            list<string>& L = hash_table[hash_func(query.s)];
            if(L.size()==0)
                L.push_front(query.s);
            else{
                it iter = find(L.begin(), L.end(), query.s);
                if(iter == L.end())
                    L.push_front(query.s);
            }
		}
		else if (query.type == "find"){
            list<string>& L = hash_table[hash_func(query.s)];
            if(L.size()==0)
                cout<<"no"<<endl;
            else{
                it iter = find(L.begin(), L.end(), query.s);
                if(iter != L.end())
                    cout<<"yes"<<endl;
                else
                    cout<<"no"<<endl;
            }

		}
		else if (query.type == "check"){
            list<string>& L = hash_table[query.ind];
            if(L.size() !=0 ){
                for_each(L.begin(), L.end(), [](const string& str){cout<<str<<" ";});
                cout<<endl;
            }else
                cout<<endl;

		}
		else{
            list<string>& L = hash_table[hash_func(query.s)];
            it iter = find(L.begin(), L.end(), query.s);
            if(iter != L.end())
                L.erase(iter);
		}

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

