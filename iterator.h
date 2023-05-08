#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>

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
    stack <Node<T>*> pila; // los primeros en entrar son los ultimos en salir

public:
    BSTIterator() : current(nullptr), type(InOrder) {}
    BSTIterator(Node<T>* &current, Type type=InOrder): type(type) { 
        // necesito que current sea el elemento con el que inicia el iterador 
        // *pila*: debe tener los demás elementos que ayudará al recorrido (no volveré a tener acceso a la raiz del arbol)

        if (type==PreOrder){ // root - left - right  // FIFO (primero saco la raiz)
            this->current = current; // listo para el recorrido
        }
        else if(type==InOrder){  // left - root - right // FILO (saco la izq primero)
            Node<T>* temp = current;
            while (temp->left){
                pila.push(temp); //guarda nodos: desde la raiz al minimo
                temp = temp->left;
            }
            this->current = temp; // current está listo para iniciar el recorrido
        }
        else if(type==PostOrder){ // left - right - root (cuando usamos dos pilas, lo vemos al revés)
            stack <Node<T>*> pila2; // servirá para agrupar elems más rápido
            pila2.push(current); // agregamos la raiz

            while (!pila2.empty()){ // mientras que no esté vacía
                Node<T>* temp = pila2.top();  pila2.pop(); // quitamos 1er elem

                pila.push(temp); // añadimos la raiz a la pila resultante
        
                if (temp->left) pila2.push(temp->left);  // añadimos izquierda
                if (temp->right) pila2.push(temp->right); // añadimos derecha
            }
            this->current = pila.top(); // current está listo para el recorrido
            pila.pop();
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
        /*
            1. Tengo la rama
            2. Si existe, guardo la izquierda.
            3. Si existe, guardo la derecha 
            (Iterativo)
        */
        if (pila.empty() && !current->left && !current->right) {current=nullptr; return;} 

        // notar que para estar aquí, ya tengo al padre
        if (current->right){
            pila.push(current->right);
        }

        if(current->left){ // debo asegurarme de poder acceder a la rama
            pila.push(current->left);
        } 
        current = pila.top(); //current es root
        pila.pop();
    }    
    
    void next_in_order(){ // left - root - right
        /* 
            1. Guarda toda la izquierda (left)
            2. Hace pop (del top)
            3. Verifica si el elemento que quitó tiene derecha:
                - Si la tiene, guarda nodo->right y toda su rama izquierda (iterativo). 
        */
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
        if (pila.empty()) {current=nullptr; return;}
        
        current = pila.top();
        pila.pop();
           
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
