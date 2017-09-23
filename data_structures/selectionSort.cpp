#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void selectionSort(vector<int>& vec){
    typedef vector<int>::iterator it;
    for(int i=0;i<vec.size()-1;++i){
        it iter = min_element(vec.begin()+i, vec.end());
        swap(*(vec.begin()+i), *iter);
    }
}

int main(){
    
    vector<int> vec = {1,3,7,2,1,2,4,9,10};
    selectionSort(vec);
    for_each(vec.begin(),vec.end(),[](const int& a){cout<<a<<" ";});
    return 0;

}
