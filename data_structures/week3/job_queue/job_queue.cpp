#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>
#include <cstdlib>

using std::vector;
using std::cin;
using std::cout;
using namespace std;

class JobQueue {
private:
    long long num_workers_;
    vector<long long> jobs_;
    vector<long long> assigned_workers_;
    vector<long long> start_times_;
    vector< pair<long long, long long> > end_times_;


    void siftup(long long i){
        while (i > 0 && (end_times_[(i-1)/2].first > end_times_[i].first || (end_times_[(i-1)/2].first == end_times_[i].first && end_times_[(i-1)/2].second > end_times_[i].second))){
            swap(end_times_[(i-1)/2] , end_times_[i]);
            i = (i-1)/2;
        }
    }
    
    void siftdown(long long i){
        long long minIndex = i;
        long long l=2*i + 1;
        if((l < end_times_.size() && end_times_[l].first < end_times_[minIndex].first)||(l < end_times_.size()&&end_times_[l].first == end_times_[minIndex].first && end_times_[l].second < end_times_[minIndex].second))//no l<end_times_.size() will result in stack overflow
            minIndex = l;
        long long r = 2*i + 2;
        if((r < end_times_.size() && end_times_[r].first < end_times_[minIndex].first)||(r < end_times_.size()&&end_times_[r].first == end_times_[minIndex].first && end_times_[r].second < end_times_[minIndex].second))//no l<end_times_.size() will result in stack overflow

            minIndex = r;
        if(i != minIndex){
            swap(end_times_[i], end_times_[minIndex]);
            siftdown(minIndex);
        }
    }

    void insert(pair<long long ,long long>p){
        end_times_.push_back(p);
        siftup((long long) end_times_.size()-1);
    }

    pair<long long ,long long> extractmin(){
        pair<long long ,long long> result = end_times_[0];
        end_times_[0]= end_times_[end_times_.size()-1];
        end_times_.pop_back();
        siftdown(0);
        return result;
    }

    void WriteResponse() const {
        for (long long i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        long long m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(long long i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        // TODO: replace this code with a faster algorithm.
        
        start_times_.resize(jobs_.size(),0);
        assigned_workers_.resize(jobs_.size(),0);
        for(long long i=0; i < jobs_.size(); ++i){
           if(end_times_.size() < num_workers_){
               assigned_workers_[i]=i;
               insert(pair<long long , long long> (start_times_[i]+jobs_[i],assigned_workers_[i]));
           }else{
               pair<long long, long long> tmp = extractmin();
               start_times_[i] = tmp.first;
               assigned_workers_[i] = tmp.second;
               insert(pair<long long, long long> (start_times_[i]+jobs_[i],assigned_workers_[i]));
           }

        }
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
