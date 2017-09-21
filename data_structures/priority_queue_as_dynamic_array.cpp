#include<iostream>
using namespace std;

class pq{
    int size;
    int capacity;
    int* ptr;
    int parent(int i){ return (i+1)/2-1;}
    int left(int i){return i*2+1;}
    int right(int i){return (i+1)*2;}
    void swap(int &a, int &b){
        int temp;
        temp = a;
        a = b;
        b = temp;
    }

    void siftup(int pos){
        if(pos == 0)
            return;
        else{
            if(ptr[pos]>ptr[parent(pos)])
                swap(ptr[pos], ptr[parent(pos)]);
            return siftup(parent(pos));
        }
    }

    void siftdown(int pos){
        int maxindex = pos;
        int l = left(pos);
        int r = right(pos);
        if(l<size && ptr[l]>ptr[maxindex])
            maxindex = l;
        if(r<size && ptr[r]>ptr[maxindex])
            maxindex = r;
        if(maxindex != pos){
            swap(ptr[pos], ptr[maxindex]);
            return siftdown(maxindex);
        }else
            return;
    }

public:
    pq():size(0), capacity(0), ptr(nullptr){}
    ~pq(){delete[] ptr;}

    int getMax(){
        if(size==0)
            throw "No elements in the heap.";
        return ptr[0];
    }

    int extractMax(){
        int result;
        if(size==0)
            throw "No elements in the heap.";
        result = ptr[0];
        ptr[0]=ptr[size-1];
        size = size - 1;
        siftdown(0);
        return result;
    }
    
    void remove(int pos){
        if(size==0)
            throw "No elements in the heap.";
        if(pos>size-1)
            throw "No element at this position.";
        ptr[pos]=INT_MAX;
        siftup(pos);
        int temp = extractMax();
    }
    
    void print(){
        for(int i=0;i<size;++i)
            cout<<ptr[i]<<" ";
        cout<<endl;
    }
    
    void insert(int a){
        if(size==0&&capacity==0){
            size++;
            capacity++;
            ptr = new int(a);
        }else{
            if(size==capacity){
                capacity*=2;
                size++;
                int* temp = new int[capacity];
                for(int i=0; i<size-1; ++i){
                    temp[i] = ptr[i];
                }
                temp[size-1]=a;
                delete[] ptr;
                ptr = temp;
            }else{
                size++;
                ptr[size-1]=a;
            }
            siftup(size-1);
        }
    }
    

};

int main(){
    try{
        pq heap;
        heap.insert(1);
        heap.insert(6);
        heap.insert(9);
        heap.insert(7);
        cout<<heap.extractMax()<<endl;
        heap.print();
        cout<<heap.extractMax()<<endl;
        heap.print();
        cout<<"Test exceptions:"<<endl;
        pq heapempty;
        heapempty.extractMax();
    }catch(const char* m){
        cout<<m<<endl;
    }

}
