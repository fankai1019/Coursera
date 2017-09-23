#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
template class std::vector<int>;
int moneyChange(int money, const vector<int> coins){
    vector<int> vec(money+1);
    vec[0]=0;
    for(int i=1; i<=money; ++i){
        vec[i] = INT_MAX;
        for(int j = 0; j < coins.size(); ++j){
            if(i >= coins[j]){
                int numCoins = vec[i-coins[j]]+1;
                if(numCoins<vec[i])
                    vec[i]=numCoins;
            }
        }
    }
    return *(vec.end()-1);
}

int main(){
    int a=9;
    vector<int> coins = {1,5,6};
    cout<<moneyChange(a, coins);
    return 0;
}
