#include<bits/stdc++.h>
using namespace std;


template<class T> struct node
{
    T val;
    struct node<T> *next;
};


int main()
{
    node<int> *head = static_cast< node<int>* >(malloc(sizeof(struct node<int>)));
    head->val = 1;
    node<int> *node1 = static_cast< node<int>* >(malloc(sizeof(struct node<int>)));
    node1->val = 2;
    head->next = node1;
    node<int> *cur = head;
    while(cur!= 0)
    {
        cout << (cur->val) << endl;
        cur = cur->next;
    }
    return 0;
}