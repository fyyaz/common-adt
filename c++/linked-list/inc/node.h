#ifndef NODE_H
#define NODE_H

template< class T > struct node
{
    // struct members
    T val;
    node<T> *next;

    // constructors
    node();
    node(T val);

    // arithmetic operators
    node operator + (node<T> &operand);
    
    // assignment operators
    void operator = (const node<T> &value);
    void operator += (const node<T> &value);
    
    // boolean operators
    bool operator < (const node<T> &value)const;
    bool operator > (const node<T> &value)const;
    bool operator >= (const node<T> &value)const;
    bool operator <= (const node<T> &value)const;
    bool operator != (const node<T> &value)const;
    bool operator == (const node<T> &value)const;
};

#endif
