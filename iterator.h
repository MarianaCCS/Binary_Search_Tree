#ifndef ITERATOR_H
#define ITERATOR_H

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
    std::stack<NodeBT<T>*> s; 
    std::queue<NodeBT<T>*> q; 

    void set_current() {
        if (type == InOrder) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            if (!s.empty()) {
                current = s.top();
                s.pop();
            }
        } else if (type == PreOrder) {
            if (current->left != nullptr) {
                s.push(current->left);
            }
            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (!s.empty()) {
                current = s.top();
                s.pop();
            } else {
                current = nullptr;
            }
        } else if (type == PostOrder) {
            std::stack<NodeBT<T>*> s2;
            s.push(current);
            while (!s.empty()) {
                NodeBT<T>* node = s.top();
                s.pop();
                s2.push(node);
                if (node->left != nullptr) {
                    s.push(node->left);
                }
                if (node->right != nullptr) {
                    s.push(node->right);
                }
            }
            if (!s2.empty()) {
                current = s2.top();
                s2.pop();
            }
        } else if (type == BFS) {
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
            if (!q.empty()) {
                current = q.front();
                q.pop();
            } else {
                current = nullptr;
            }
        }
    }

public:
    BSTIterator() : current(nullptr), type(InOrder) {};
    BSTIterator(NodeBT<T> *current, Type type=InOrder): current(current), type(type) {
        set_current();
    }

    BSTIterator(const BSTIterator<T>& other) : current(other.current), type(other.type), s(other.s), q(other.q) {}

    BSTIterator<T>& operator=(const BSTIterator<T>& other) {
        current = other.current;
        type = other.type;
        s = other.s;
        q = other.q;
        return *this;
    }

    bool operator!=(const BSTIterator<T>& other) {
        return current != other.current;
    }

    BSTIterator<T>& operator++() {   //++it
        if (type == InOrder) {
            if (current->right != nullptr) {
                s.push(current->right);
                current = current->right->left;
                while (current != nullptr) {
                    s.push(current);
                    current = current->left;
                }
            } else if (!s.empty()) {
                current = s.top();
                s.pop();
            } else {
                current = nullptr;
            }
        } else if (type == PreOrder) {
            if (current->left != nullptr) {
                            s.push(current->left);
        }
        if (current->right != nullptr) {
            s.push(current->right);
        }
        if (!s.empty()) {
            current = s.top();
            s.pop();
        } else {
            current = nullptr;
        }
    } else if (type == PostOrder) {
        if (s.empty()) {
            current = nullptr;
        } else if (s.top()->right != nullptr && s.top()->right != current) {
            current = s.top()->right;
            while (current->left != nullptr || current->right != nullptr) {
                if (current->left != nullptr) {
                    s.push(current->left);
                    current = current->left;
                } else if (current->right != nullptr) {
                    s.push(current->right);
                    current = current->right;
                }
            }
        } else {
            current = s.top();
            s.pop();
        }
    } else if (type == BFS) { //busqueda en amplitud
        if (q.empty()) {
            current = nullptr;
        } else {
            current = q.front();
            q.pop();
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    return *this;
}

T operator*() {
    return current->data;
}
};

#endif