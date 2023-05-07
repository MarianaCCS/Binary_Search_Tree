#include "bst.h"


void test_bst(){
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
}

void test_iterators(){
    BSTree<int>* bstree = new BSTree<int>();
    bstree->insert(8);
    bstree->insert(3);
    bstree->insert(1);
    bstree->insert(6);
    bstree->insert(4);
    bstree->insert(7);
    bstree->insert(10);
    bstree->insert(14);
    bstree->insert(13);

    string result = "";
    BSTree<int>::iterator ite = bstree->begin(BSTIterator<int>::Type::InOrder);
    while(ite != bstree->end()) {
        result += std::to_string(*ite) + " ";
        ++ite;
    } 
    cout<<"Iterator InOrder: "<<result<<endl; //result == "8 3 1 6 4 7 10 14 13 "

    result = "";
    BSTree<int>::iterator ite1 = bstree->begin(BSTIterator<int>::Type::PreOrder);
    while(ite1 != bstree->end()) {
        result += std::to_string(*ite1) + " ";
        ++ite1;
    }
    cout<<"Iterator PreOrder: "<<result; //result == "8 3 1 6 4 7 10 14 13 "
    
    result = "";
    BSTree<int>::iterator ite2 = bstree->begin(BSTIterator<int>::Type::PostOrder);
    while(ite2 != bstree->end()) {
        result += std::to_string(*ite2) + " ";
        ++ite2;
    }
    cout<<"Iterator PostOrder: "<<result; //result == "8 3 1 6 4 7 10 14 13 "
    //result == "1 4 7 6 3 13 14 10 8 "

}

int main(){
    test_iterators();
    return 0;
}