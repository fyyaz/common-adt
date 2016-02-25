#include<iostream>
#define nullptr 0
using namespace std;

template< class key_t > class node{
    public:
      key_t val;
      node <key_t> *left,*right;
    node(){}
    node(key_t _val){
      val = _val;
      left = nullptr;
      right = nullptr;
    }
    bool operator > (const node&n){
       return val > n->val;
    }
    void operator = (const node&n){
        val = n->val;
        left = n->left;
        right = n->right;
    }
};


template< class key_t > class priority_queue{
    #define MAXN 1000
    int size;
    node<key_t> heap[MAXN];
    public:
      priority_queue(){
        size = 0;
      }
    public:
      void push(key_t T){
          if(heap[0] == nullptr)
             heap[0] = new (node<key_t>){T};
          else{
             for(int pos = ++size;heap[pos]val > heap[pos/2]val;pos = pos/2){
                 heap[pos] = heap[pos/2];
             }
          }
      }

    #undef MAXN
};

int main(){
   priority_queue<int>pq;
   pq.push(1);
}