#include <iostream>
#include <vector>
using namespace std;

template class std::vector<int>;
vector<int> Merge(const vector<int>& A, const vector<int>& B){
    vector<int> result;
    typedef vector<int>::const_iterator it;
    it ita = A.begin();
    it itb = B.begin();
    while(ita != A.end() && itb != B.end()){
        if(*ita < *itb){
            result.push_back(*ita);
            ita++;
        }else{
            result.push_back(*itb);
            itb++;
        }
    }
    if(ita == A.end())
        result.insert(result.end(), itb, B.end());
    else
        result.insert(result.end(), ita, A.end());

    return result;
}

vector<int> MergeSort(const vector<int>& A){
    if(A.size()==1)
        return A;
    int m = A.size()/2;
    vector<int> Afront(A.begin(), A.begin() + m);
    vector<int> Aback(A.begin() + m, A.end());
    vector<int> B = MergeSort(Afront);
    vector<int> C = MergeSort(Aback);
    return Merge(B, C);
}

int main(){
    vector<int> vec = {1, 10, 2, 9, 8, 7, 100, 89, 4, 32};
    vector<int> result = MergeSort(vec);
    for(auto i : result)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
