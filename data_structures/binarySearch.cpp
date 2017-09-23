#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int binarySearch(const vector<int>& vec, int low, int high, int key){
    int mid = (high+low)/2;
    if(low>high)
        return 0;
    if(vec[mid]==key)
        return mid;
    else if(key>vec[mid])
        return binarySearch(vec, mid+1, high, key);
    else
        return binarySearch(vec, low, mid-1, key);

}

int main(){
    vector<int> vec = {1,2,3,5,8,10};
    cout<<binarySearch(vec, 0, vec.size()-1, 8);
    return 0;

}
