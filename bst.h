#include "node.h"
#include <stack>
using namespace std;


template <class T>
class BSTree{ // Binary Search Tree
    Node<T>* root;

    public:
    BSTree():root(nullptr){}


    // insercion
    void insert_rec(Node<T>*& it,Node<T>* nuevo){
        if (!it) it=nuevo;
        else if(nuevo->data>it->data) insert_rec(it->right,nuevo);
        else if (nuevo->data<it->data) insert_rec(it->left,nuevo);
        else cerr<<"Elemento ya se encuentra"<<endl;
    }

    void insert(T _data){
        insert_rec(root,new Node<T>(_data));
    }

    // PreOrder
    void preorder_rec(Node<T>* nodo){
        if (!nodo){cout<<endl; return;}
        cout<<nodo->data;
        preorder_rec(nodo->left);
        preorder_rec(nodo->right);
    }

    void displayPreOrder(){
        preorder_rec(root); cout<<endl;
    }

    // InOrder
    void inorder_rec(Node<T>* nodo){
        if (!nodo){cout<<" "; return;}
        inorder_rec(nodo->left);
        cout<<nodo->data<<" ";
        inorder_rec(nodo->right);
    }

    void displayInOrder(){
        inorder_rec(root); cout<<endl;
    }

    // PostOrder
    void postorder_rec(Node<T>* nodo){
        if (!nodo){cout<<endl; return;}
        postorder_rec(nodo->left);
        postorder_rec(nodo->right);
        cout<<nodo->data<<" ";
    }

    void displayPostOrder(){
        postorder_rec(root); cout<<endl;
    }

    // funcion para encontrar si un elemento pertenece
    pair<bool,Node<T>**> find(Node<T>*& nodo, T _data){ // nodo debe pasarse por referencia
        if (!nodo) return pair<bool,Node<T>**>(false,nullptr);
        
        if (_data<nodo->data) return find(nodo->left,_data);
        else if(_data>nodo->data) return find(nodo->right,_data);
        else return pair<bool,Node<T>**>(true, &nodo); // en este caso, se encontró (_data==nodo->data)
    }

    void remove(T _data){ // considerando 3 casos: nodo hoja, con un hijo, con dos hijos
        pair<bool, Node<T>**> result = find(root,_data); // (*result.second): Node<T>*}

        /* // Ejemplo de su uso
        if (result.first) cout<<(*result.second)->data;
        else{ cout<<"No se encuentra";}
        */
       if (!result.first){ cerr<<"Elemento no encontrado"<<endl; return; }
       if ((*result.second)->left && (*result.second)->right){ // con dos hijos
            Node<T>* temp = min((*result.second)->right);
            T res = temp->data;
            remove(temp->data);
            (*result.second)->data = res; // se guarda nuevo valor
            temp->killSelf();
       }
       else if(!(*result.second)->left && !(*result.second)->right){ // cero hijos
            (*result.second)->killSelf();
            (*result.second) = nullptr;
       }
       else{ // con un hijo
            if ((*result.second)->left){
                Node<T>* elim = *result.second;
                (*result.second)=(*result.second)->left;
                elim->killSelf();
            }
            else {
                Node<T>* elim = *result.second;
                (*result.second)=(*result.second)->right;
                elim->killSelf();
            }
       }
    }

    Node<T>* min(Node<T>*& nodo){
        Node<T>* temp = nodo;
        while (temp->left) temp = temp->left;
        return temp;
    }

    Node<T>* max(Node<T>*& nodo){
        Node<T>* temp = nodo;
        while (temp->right) temp = temp->right;
        return temp;
    }

    T minimo(){
        return min(root)->data;
    }

    T maximo(){
        return max(root)->data;
    }

    T sucesor(T _data){ // para encontrar el siguiente valor
        pair<bool,Node<T>**> result = find(root,_data);
        if (!result.first){cerr<<"Elemento no encontrado"<<endl; } // no se encuentra
        else{
            if((*result.second)==max(root)){cerr<<"Elemento sin sucesor "; return _data;}
            else if((*result.second)->right){
                return min((*result.second)->right)->data;
            }
            else{ // no tiene hijo derecho, así que sucesor debe obtenerse con un stack
                stack<T> pila; // First Input, Last Output

                Node<T>* temp = root;
                
                while (_data!=temp->data && temp){  // hay que guardar los elementos
                    if (_data<temp->data){
                        pila.push(temp->data); // guardamos los de la izquierda
                        temp = temp->left;
                    }
                    else{
                        pila.push(temp->data);
                        temp = temp->right;
                    }
                } // se termina de añadir elementos al stack

                // haremos pop
                while (pila.top()<=_data){ // se tiene que quitar todos los que son menores e iguales
                    pila.pop();
                }
                return pila.top();
            }
        }
        return T();
    }

    T predecesor(T _data){
        pair<bool,Node<T>**> result = find(root,_data); // verificamos si se encuentra 

        if (!result.first){ cerr<<"Elemento no encontrado"<<endl;}
        else if (_data==min(root)->data){cout<<"Elemento sin predecesor ";return _data;}  // es el minimo
        else{ // se encontró y tiene predecesor
            if ((*result.second)->left){ // tiene hijo izquierdo
                return max((*result.second)->left)->data;
            }
            else{ // tenemos al menor valor de un subarbol derecho 
                stack<T> pila;
                Node<T>* temp = root;
                while (temp->data!=_data && temp){ // se guarda desde la raiz a la data
                    if (_data<temp->data){ // se añade queremos conseguir el menor
                        pila.push(temp->data);
                        temp = temp->left; // vamos a la izquierda
                    }
                    else{ // vamos a la derecha
                        pila.push(temp->data);
                        temp = temp->right;
                    }
                } // ya guardamos los elementos

                while (pila.top()>=_data){ // quitamos todos los mayores e iguales
                    pila.pop();
                } // hacemos pop hasta que se llegue 
                return pila.top();
            }
        }
        return T();
    }

    void size_rec(Node<T>*& nodo,int& len){
        if (!nodo){return;}
        else{
            size_rec(nodo->left, len);
            size_rec(nodo->right, len);
            len++;
        }
    }

    int size(){
        if (!root) return 0;
        int result = 0;
        size_rec(root,result);
        return result;
    }

    int altura_rec(Node<T>*& nodo){
        if (!nodo) return 0;
        int altura_izq = altura_rec(nodo->left);
        int altura_der = altura_rec(nodo->right);
        return 1+((altura_izq>altura_der)?altura_izq:altura_der);
    }

    int altura(){
        if (!root) return -1;
        return altura_rec(root);
    }

    bool lleno(Node<T>*& nodo){
        if ((nodo->left && nodo->right)|| (!nodo->left && !nodo->right)) return true;
        return false;
    }

    bool lleno_rec(Node<T>*& nodo){
        if (!nodo) return true;
        else if(!lleno(nodo)) return false;
        else return lleno_rec(nodo->left) && lleno_rec(nodo->right);
    }

    bool arbol_lleno(){
        return lleno_rec(root);
    }

    void clear(){
        root->killSelf();
        root = nullptr; 
    }
    
    void displayBFS(){ // recorrido en profundidad (inorder)
        inorder_rec(root);
    }

    ~BSTree(){ clear(); }
};  