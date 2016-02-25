#include<iostream>
#define nullptr 0
using namespace std;

template< class key_t > class node{
    public:
      key_t val;
      node <key_t> *next;
    node(){}
    node(key_t _val){
      val = _val;
      next = nullptr;
    }
};

template< class key_t > class linked_list{
    node<key_t>*begin;
  public:
    linked_list(){begin = nullptr;}
  public:
    void push_back(key_t T){
        if(begin == nullptr)
           begin = new (node<key_t>){T};
        else{
            node<key_t>*current = begin;
            while(current->next != nullptr){
              // cout << current->val << endl;
               current = current->next;
            }
            if(current->next == nullptr){
               current->next = new (node<key_t>){T};
            }
        }
    }
    void pop_back(){
        node<key_t>*current = begin;
        if(begin->next == nullptr)
           delete[]begin;
        else{
          while(current->next != nullptr){
              current = current->next;
          }
          delete[]current;
        }
    }
    key_t get(int x){
       node<key_t>*current = begin;
       int it = 0;
       while(it != x && current->next != nullptr){
          current = current->next;
          it++;
       }
       return current->val;
    }
    void erase(int x){
       if(begin == nullptr)
         return;
       else if(x == 0){
          node<key_t>*nbegin = begin->next;
          delete[]begin;
          begin = nbegin;
       }
       else{
         node<key_t>*current = begin;
         int it = 0;
         while(it+1 != x && current->next != nullptr){
            current = current->next;
            it++;
         }
         if(current != nullptr)
            current->next = current->next->next;
       }
    }
    bool empty(){
       return begin == nullptr;
    }
};
template< class key_t > class queue{
    linked_list<key_t>list;
    public:
      queue(){}
    public:
      void push(key_t val){
        list.push_back(val);
      }
      key_t front(){
         return list.get(0);
      }
      void pop(){
         list.erase(0);
      }
      bool empty(){
         return list.empty();
      }
};

int main(){
  queue<int>qq;
  for(int i = 0;i < 10;i++){
    qq.push(i);
  }
  while(!qq.empty()){
     cout << qq.front() << endl;
     qq.pop();
  }

}