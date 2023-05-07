#ifndef ITERATOR_H
#define ITERATOR_H

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
    Node<T> *current;
    Type type;
    stack <Node<T>*> pila;
    queue <Node<T>*> cola;

public:
    BSTIterator() : current(nullptr), type(InOrder) {}
    BSTIterator(Node<T>* &current, Type type=InOrder): type(type) {
        if (type==PreOrder){ // root - left - right  // FIFO (primero saco la raiz)
            Node<T>* temp = current;
            while (current->left && current){
                cola.push(temp); //guarda nodos: desde la raiz al minimo
                temp = current->left;
            }
            this->current = cola.pop(); // listo para el recorrido
        }
        else if(type==InOrder){  // left - root - right // FILO (saco la izq primero)
            Node<T>* temp = current;
            while (temp->left){
                pila.push(temp); //guarda nodos: desde la raiz al minimo
                temp = temp->left;
            }
            this->current = temp; // current está listo para iniciar el recorrido
        }
        else{

        }
    }


    BSTIterator<T> &operator=(BSTIterator<T> other){
        return *other;
    }

    bool operator!=(BSTIterator<T> other){
        if (!other.current && !this->current)return false;
        else if(!other.current || !this->current)  return true;
        return other.current->data != this->current->data;
    }


    void next_pre_order(){ // root - left -right
        // notar que para estar aquí, ya tengo al padre
        if(current->left) current = current->left;
        else if (current->right) current = current->right;
        else if (!cola.empty()) current = cola.front();
        cola.pop(); // siempre  quito al padre
    }    
    
    void next_in_order(){ // left - root - right
        if (pila.empty() && !current->right) {
            current=nullptr;  return; // caso en el que se recorre todo 
        }
        current = pila.top(); //current actualiza su valor
        pila.pop(); // notar que lo puedo eliminar porque no tiene + hijos izquierdos 
        if (current->right) {
            Node<T>* temp = current->right; // puede tener hijos izquierdos
            while(temp->left) {
                pila.push(temp); // puede tener lado izquierdo
                temp = temp->left;
            }
            pila.push(temp); //se añade al ultimo elemento que falta 
        }      
    }

    void next_post_order(){

    }

    BSTIterator<T>& operator++(){   //++it
        if (type==PreOrder) next_pre_order();
        else if(type==InOrder) next_in_order();
        else if(type==PostOrder) next_post_order();
        return *this;
    }

    T operator*(){
        return current->data;
    }
};

#endif
