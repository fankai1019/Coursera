#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int groups(vector<double>& ages){
    sort(ages.begin(), ages.end());
    double l = ages[0];
    double r = l + 1;
    int count = 0;
    vector<vector<double>> result(100);
    int i = 0;
    while(l != ages[ages.size()]){
        double temp = ages[i];
        while(i < ages.size() && ages[i]<=r){
            result[count].push_back(ages[i]);
            i++;
        }
        for_each(result[count].begin(),result[count].end(),[](const double& a){cout<<a<<" ";});
        cout<<endl;
        l = ages[i];
        r = l + 1;
        count++;
    }
    return count;
}

int main(){
    vector<double> ages = {10, 2.0, 4.5, 4.6, 2.1, 2.2, 2.3, 3.3};
    cout<<groups(ages)<<endl;

    return 0;
}
