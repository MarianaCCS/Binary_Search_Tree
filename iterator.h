#ifndef ITERATOR_H
#define ITERATOR_H
/*
#include "node.h"
#include <stack>
#include <queue>
template <typename T>
class BSTIterator
{
public:
    enum Type {
        PreOrder, InOrder, PostOrder, BFS
    };

private:
    NodeBT<T> *current;
    Type type;
    stack <T> pila;


public:

    BSTIterator() : current(nullptr), type(InOrder) {};
    BSTIterator(NodeBT<T> *current, Type type=InOrder): type(type), current(current) {
        if (type==PreOrder){ // implementar stack para preorder

        }
        else if(type==InOrder){

        }
    }

    BSTIterator<T> &operator=(BSTIterator<T> other);
    bool operator!=(BSTIterator<T> other){
        return other.current != this->current;
    }

    BSTIterator<T> &operator++(){   //++it
        if (type==InOrder){
            
        }
    }
    T operator*(){
        return current->data;
    }
};
*/
#endif
