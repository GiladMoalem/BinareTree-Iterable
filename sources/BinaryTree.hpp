#pragma once
#include <list>
#include <iostream>

namespace ariel{

template <typename T>
class BinaryTree{

private:
    struct Node{
    public:
    T data;
    Node* right;    
    Node* left;    

    Node(T& data, Node* right=nullptr, Node* left=nullptr)
    :data(data), right(right), left(left){}
    };
    
Node* _head;
std::list<T> list_order;

public:
BinaryTree():
_head(nullptr){}

BinaryTree& add_root(T head);
BinaryTree& add_left(T father,T left);
BinaryTree& add_right(T father,T right);

typename std::list<T>::iterator begin_preorder(){
    return list_order.begin();
}

typename std::list<T>::iterator end_preorder(){
    return list_order.end();
}

typename std::list<T>::iterator begin_inorder(){
    return list_order.begin();
}

typename std::list<T>::iterator end_inorder(){
    return list_order.end();
}

typename std::list<T>::iterator begin_postorder(){
    return list_order.begin();
}

typename std::list<T>::iterator end_postorder(){
    return list_order.end();
}

typename std::list<T>::iterator begin(){
    return begin_inorder();
}

typename std::list<T>::iterator end(){
    return end_inorder();
}

template <typename E> friend std::ostream& operator<<(std::ostream& os, BinaryTree<E> const &tree);

};




template<typename T> BinaryTree<T>& BinaryTree<T>::add_root(T head){
return *this;
}

template<typename T> BinaryTree<T>& BinaryTree<T>::add_left(T father,T left){
    return *this;
}
template<typename T> BinaryTree<T>& BinaryTree<T>::add_right(T father,T right){
    return *this;
}


template<typename T> std::ostream& operator<<(std::ostream& os, BinaryTree<T> const &tree){
    return os<<"PRINT BinaryTree";
}


} 