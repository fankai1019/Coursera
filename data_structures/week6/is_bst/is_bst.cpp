#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void InOrder(int i, const vector<Node>& tree, vector<int>& results){

    if(i==-1)
        return;
    InOrder(tree[i].left,tree,results);
    //do something
    results.push_back(tree[i].key);
    InOrder(tree[i].right,tree,results);
    
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    // Implement correct algorithm here
    if(tree.empty())
        return true;
    vector<int> results;
    InOrder(0,tree, results);
    for(int i=0;i<results.size()-1;++i){
        if(results[i]>=results[i+1])
            return false;
    }
    return true;
}



int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    
    
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
  return 0;
}
