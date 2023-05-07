#include <iostream>
using namespace std;


template <class T>
struct Node{
    Node<T>* left;
    Node<T>* right;
    T data;

    Node():left(nullptr),right(nullptr){}
    Node(T _data):left(nullptr),right(nullptr),data(_data){}

    void killSelf(){
        if (left) left=nullptr;
        if (right) right = nullptr;
    }

    void finish(){
        if (left) left->finish();
        if (right) right->finish();
        delete this;
    }

    ~Node(){ }
};