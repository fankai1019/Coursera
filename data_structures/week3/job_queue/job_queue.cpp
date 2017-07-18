#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>


using std::vector;
using std::cin;
using std::cout;
using namespace std;

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;
    vector< pair<long long, int> > end_times_;

    void siftup(long long i){
        while (i > 0 && end_times_[(i-1)/2].first > end_times_[i].first){
            swap(end_times_[(i-1)/2] , end_times_[i]);
            i = (i-1)/2;
        }
    }
    
    void siftdown(int i){
        int minIndex = i;
        int r = 2*i + 2;
        if(r < end_times_.size() && end_times_[r].first <= end_times_[minIndex].first){
            minIndex = r;
            swap(end_times_[i], end_times_[minIndex]);
        }
        int l=2*i + 1;
        if(l < end_times_.size() && end_times_[l].first <= end_times_[minIndex].first){
            minIndex = l;
            swap(end_times_[i], end_times_[minIndex]);
        }
        if(i != minIndex){
//            swap(end_times_[i], end_times_[minIndex]);
            siftdown(minIndex);
        }
    }

    void insert(pair<long long ,int>p){
        end_times_.push_back(p);
        siftup((int) end_times_.size()-1);
    }

    pair<long long ,int> extractmin(){
        pair<long long ,int> result = end_times_[0];
        end_times_[0]= end_times_[end_times_.size()-1];
        end_times_.pop_back();
        siftdown(0);
        return result;
    }

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        // TODO: replace this code with a faster algorithm.
        
        start_times_.resize(jobs_.size(),0);
        assigned_workers_.resize(jobs_.size(),0);
        for(int i=0; i < jobs_.size(); ++i){
           if(end_times_.size() != num_workers_){
               assigned_workers_[i]=i;
               end_times_.push_back(pair<long long , int> (start_times_[i]+jobs_[i],assigned_workers_[i]));
           }else{
               pair<long long, int> tmp = extractmin();
               start_times_[i] = tmp.first;
               assigned_workers_[i] = tmp.second;
               insert(pair<long long, int> (start_times_[i]+jobs_[i],assigned_workers_[i]));
           }

        }
//        assigned_workers_.resize(jobs_.size());
//        start_times_.resize(jobs_.size());
//        vector<long long> next_free_time(num_workers_, 0);
//        for (int i = 0; i < jobs_.size(); ++i) {
//            int duration = jobs_[i];
//            int next_worker = 0;
//            for (int j = 0; j < num_workers_; ++j) {
//                if (next_free_time[j] < next_free_time[next_worker])
//                next_worker = j;
//            }
//            assigned_workers_[i] = next_worker;
//            start_times_[i] = next_free_time[next_worker];
//            next_free_time[next_worker] += duration;
//        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
