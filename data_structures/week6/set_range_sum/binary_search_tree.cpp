#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;

struct Node{
    Node(int k):key(k), height(1), parent(nullptr), left(nullptr), right(nullptr){}
    Node(int k, int h, Node* p, Node* l, Node* r):key(k), height(h), parent(p), left(l), right(r){}
    int key;
    int height;
    Node* parent;
    Node* left;
    Node* right;

};

int height(Node* root){
    if(root == nullptr)
        return 0;
    else
        return 1+max(height(root->right), height(root->left));
}

int treesize(Node* root){
    if(root == nullptr)
        return 0;
    else
        return 1+treesize(root->right)+treesize(root->left);
}

Node* find(int key, Node* root){
    if(root->key == key)
        return root;
    else if(root->key > key){
        if(root->left != nullptr)
            return find(key, root->left);
        return root;
    }
    else{
        if(root->right != nullptr)
            return find(key, root->right);
        return root;
    }
}


Node* leftDecsendant(Node* node){
    if(node->left == nullptr)
        return node;
    else
        return leftDecsendant(node->left);
}

Node* rightAncester(Node* node){
    if(node->key < node->parent->key)
        return node->parent;
    else 
        return rightAncester(node->parent);
}

Node* next(Node* node){
    if(node->right != nullptr)
        return leftDecsendant(node->right);
    else 
        return rightAncester(node);
}

void insert(int key, Node* root){
    Node* p = find(key, root);
    if(key < p->key)
        p->left = new Node(key, 1, p, nullptr, nullptr);
    else
        p->right = new Node(key, 1, p, nullptr, nullptr);
        
}

void remove(Node* node){
    if(node->right == nullptr && node->left == nullptr){
        if(node->parent->left == node)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
    }else if(node->right==nullptr){
        Node* nodeleft = node->left;
        Node* p = node->parent;
        if(p->left == node)
            p->left = nodeleft;
        else
            p->right = nodeleft;
        
        nodeleft->parent=p;
    }else{
        Node* p = node->parent;
        Node* noderight = node->right;
        Node* x = next(node);
        //x->left is nullptr already
        Node* xparent = x->parent;
        if(p->left == node)
            p->left = x; 
        else
            p->right = x;
        x->parent = p;
        x->left = node->left;
        if(node->left!=nullptr)
            node->left->parent = x;
        xparent->left = x->right;
        if(node->right != x){
            x->right->parent = xparent;
            x->right = node->right;
            node->right->parent = x;
        }
    }
    delete node;
}

void rotateRight(Node* x){
    Node* p = x->parent;
    Node* y = x->left;
    Node* b = y->right;
    y->parent = p;
    if(p->left == x)
        p->left = y;
    else
        p->right = y;
    x->parent = y;
    y->right = x;
    b->parent = x;
    x->left = b;
}
void rotateLeft(Node* y){
    Node* p = y->parent;
    Node* x = y->right;
    Node* b = x->left;
    x->parent = p;
    if(p->left == y)
        p->left = x;
    else
        p->right = x;
    x->left = y;
    y->parent = x;
    y->right = b;
    b->parent =y;
    
}

void inorder(Node* root){
    if(root == nullptr)
        return;
    inorder(root->left);
    cout<<root->key<<" ";
    inorder(root->right);
}

void breathfirst(Node* root){
    queue<Node*> NodeQueue;
    NodeQueue.push(root);
    while(!NodeQueue.empty()){
        Node* temp = NodeQueue.front();
        NodeQueue.pop();
        cout<<temp->key<<" ";
        if(temp->left!=nullptr)
            NodeQueue.push(temp->left);
        if(temp->right!=nullptr)
            NodeQueue.push(temp->right);
    }
    cout<<endl;

}

int rangeSum(int l, int r, Node* root){
    int sum = 0;
    Node* node;
    while(node = find(l, root), node->key <=r){
        if(node->key==l)
            sum+=node->key;
        Node* p = next(find(l,root));
        l = p->key;
    }
    return sum;
}

int main(){
    Node root(8);
    insert(5,&root);
    insert(6,&root);
    insert(1,&root);
    insert(7,&root);
    insert(3,&root);
    insert(2,&root);
    Node* pnext = next(find(3,&root));
    cout<<"the next element is :"<<pnext->key<<endl;
    remove(find(5,&root));
    inorder(&root);
    cout<<endl;
    remove(find(7,&root));
    inorder(&root);
    cout<<endl;
    remove(find(2,&root));
    inorder(&root);
    cout<<endl;
    insert(2, &root);
    insert(5, &root);
    insert(7,&root);
    inorder(&root);
    cout<<endl;
    breathfirst(&root);
    cout<<endl;
    cout<<"The height of the tree is: "<<height(&root)<<endl;
    cout<<"The size of the tree is: "<<treesize(&root)<<endl;

    return 0;
}
