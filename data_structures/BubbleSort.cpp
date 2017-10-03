#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void BubbleSort(vector<int>& ivec){
    for(int i=0;i<ivec.size();i++)
        for(int j=0;j<ivec.size()-1;j++)
            if(ivec[j]>ivec[j+1])
                swap(ivec[j], ivec[j+1]);
}

int main(){
    vector<int> ivec = {1 ,2 ,7, 3, 8, 22, 77, 12};
    for_each(ivec.begin(), ivec.end(), [](int x){cout<<x<<" ";});
    cout<<endl;
    BubbleSort(ivec);
    for_each(ivec.begin(), ivec.end(), [](int x){cout<<x<<" ";});
    cout<<endl;

    return 0;
}
