#include "bst.h"

int main(){
    BSTree<int> arbol;

    arbol.insert(5);
    arbol.insert(10);
    arbol.insert(16);
    arbol.insert(20);
    arbol.insert(3);
    arbol.insert(2);
    arbol.insert(4);
    arbol.insert(15);
    arbol.insert(14);
    arbol.insert(11);
    cout<<"InOrder: ";arbol.displayInOrder();

    arbol.remove(5);
    
    
    cout<<"InOrder: ";arbol.displayInOrder();

    cout<<"Maximo: "<<arbol.maximo()<<endl;
    cout<<"Minimo: "<<arbol.minimo()<<endl;

    cout<<"Sucesor de 10: "<<arbol.sucesor(10)<<endl;
    cout<<"Sucesor de 16: "<<arbol.sucesor(16)<<endl;
    cout<<"Sucesor de 11: "<<arbol.sucesor(11)<<endl;
    cout<<"Sucesor de 14: "<<arbol.sucesor(14)<<endl;

    cout<<"Predecesor de 10: "<<arbol.predecesor(10)<<endl;
    cout<<"Predecesor de 4: "<<arbol.predecesor(4)<<endl;
    cout<<"Predecesor de 15: "<<arbol.predecesor(15)<<endl;

    cout<<"Size: "<<arbol.size()<<endl;
    cout<<"Altura: "<<arbol.altura()<<endl;

    arbol.clear();
    cout<<"Size: "<<arbol.size()<<endl;
    return 0;
}