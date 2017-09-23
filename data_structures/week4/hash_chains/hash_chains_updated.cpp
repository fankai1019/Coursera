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
	list<pair<size_t, list<string>>> hash_table;
	typedef list <pair<size_t, list<string>>>::iterator it;
	size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {}

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
			size_t hashvalue = hash_func(query.s);
			it iter = find_if(hash_table.begin(), hash_table.end(), [=](const pair<size_t, list<string>>& a){return a.first == hashvalue; });
			if (iter == hash_table.end())
				hash_table.push_back(make_pair(hashvalue, list<string>{query.s})); 
			else{
				list<string>::iterator inneriter = find(iter->second.begin(), iter->second.end(), query.s);
				if (inneriter == iter->second.end())
					iter->second.push_front(query.s);
			}
		}
		else if (query.type == "find"){
			size_t hashvalue = hash_func(query.s);
			it iter = find_if(hash_table.begin(), hash_table.end(), [=](const pair<size_t, list<string>>& a){return a.first == hashvalue; });
			if (iter != hash_table.end()){
				list<string>::iterator inneriter = find(iter->second.begin(), iter->second.end(), query.s);
				if (inneriter != iter->second.end())
					cout << "yes" << endl;
				else
					cout << "no" << endl;
						
			}
			else
				cout << "no" << endl;
		}
		else if (query.type == "check"){
			size_t hashvalue = query.ind;
			it iter = find_if(hash_table.begin(), hash_table.end(), [=](const pair<size_t, list<string>>& a){return a.first == hashvalue; });
			if (iter != hash_table.end()){
				for_each(iter->second.begin(), iter->second.end(), [](const string& str){cout << str << " "; });
				cout << endl;
			}else
                cout<<endl;
		}
		else{
			size_t hashvalue = hash_func(query.s);
			it iter = find_if(hash_table.begin(), hash_table.end(), [=](const pair<size_t, list<string>>& a){return a.first == hashvalue; });
			if (iter != hash_table.end()){
				list<string>::iterator inneriter = find(iter->second.begin(), iter->second.end(), query.s);
				if (inneriter != iter->second.end())
					iter->second.erase(inneriter);
			}
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

