#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using namespace std;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void siftup(int i){
        while(i > 0 && data_[(i - 1) / 2] > data_[i]){
            swap(data_[(i - 1) / 2],data_[i]);
            i = (i - 1) / 2;
        }
    }

    void siftdown(int i){
        int minIndex = i;
        int l = 2 * i + 1;
        if ( l < data_.size() && data_[l] < data_[minIndex])
            minIndex = l;
        int r = 2 * i + 2;
        if ( r < data_.size() && data_[r] < data_[minIndex])
            minIndex = r;
        if ( i != minIndex){
            swap(data_[i], data_[minIndex]);
            swaps_.push_back(make_pair(i, minIndex));
            siftdown( minIndex );
        }
    }

    void insert(int p){
        data_.push_back(p);
        siftup((int) data_.size());
    }

    int extractmin(){
        int result = data_[0];
        data_[0] = data_[data_.size()];
        data_.pop_back();
        siftdown(0);
        return result;
    }

    void remove(int i){
      data_[i] = INT_MIN;
      siftup(i);
      extractmin();
   }
    
    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void GenerateSwaps() {
        swaps_.clear();
        int size = data_.size();
        for(int i = size/2 -1; i>=0; --i)
            siftdown(i);
            
        // The following naive implementation just sorts 
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap, 
        // but in the worst case gives a quadratic number of swaps.
        //
        // TODO: replace by a more efficient implementation
//        for (int i = 0; i < data_.size(); ++i)
//            for (int j = i + 1; j < data_.size(); ++j) {
//            if (data_[i] > data_[j]) {
//                swap(data_[i], data_[j]);
//                swaps_.push_back(make_pair(i, j));
//            }
//        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
