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
        if((l < end_times_.size() && end_times_[l].first < end_times_[minIndex].first)||(end_times_[l].first == end_times_[minIndex].first && end_times_[l].second < end_times_[minIndex].second))
            minIndex = l;
        long long r = 2*i + 2;
        if((r < end_times_.size() && end_times_[r].first < end_times_[minIndex].first)||(end_times_[r].first == end_times_[minIndex].first && end_times_[r].second < end_times_[minIndex].second))
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
           if(end_times_.size() != num_workers_){
               assigned_workers_[i]=i;
               insert(pair<long long , long long> (start_times_[i]+jobs_[i],assigned_workers_[i]));
           }else{
               pair<long long, long long> tmp = extractmin();
               start_times_[i] = tmp.first;
               assigned_workers_[i] = tmp.second;
               insert(pair<long long, long long> (start_times_[i]+jobs_[i],assigned_workers_[i]));
           }

        }
//        assigned_workers_.resize(jobs_.size());
//        start_times_.resize(jobs_.size());
//        vector<long long> next_free_time(num_workers_, 0);
//        for (long long i = 0; i < jobs_.size(); ++i) {
//            long long duration = jobs_[i];
//            long long next_worker = 0;
//            for (long long j = 0; j < num_workers_; ++j) {
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
        test();
//        ReadData();
        AssignJobs();
        WriteResponse();
    }
    void test(){
            long long m = rand()%100000+1;
            num_workers_=rand()%m +1;
            jobs_.resize(m);
            for(long long i = 0; i< m;++i)
                jobs_[i]=(rand()%1000000000);
            cerr<<m<<endl;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    while(true){
        JobQueue test;
        test.Solve();
    }
//    JobQueue job_queue;
//    job_queue.Solve();
    return 0;
}
