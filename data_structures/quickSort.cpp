#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
template class std::vector<int>;

int partition(vector<int>& A, int l, int r){
    int x = A[l];
    int j = l;
    for(int i = l+1; i<=r; ++i){
        if(A[i] < x){
            j++;
            swap(A[i], A[j]);
        }
    }
    swap(A[l], A[j]);
    return j;
}

void quickSort(vector<int>& A, int l, int r){
    if(l>r)
        return;
    int m = partition(A, l ,r);
    quickSort(A, l, m-1);
    quickSort(A, m+1, r);
}

int main(){
    vector<int> vec = {1, 20, 38, 22, 3, 5, 29, 90, 100};
    quickSort(vec, 0, vec.size()-1);
    for(auto i : vec)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
