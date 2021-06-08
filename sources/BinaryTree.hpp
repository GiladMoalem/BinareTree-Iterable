#pragma once
#include <list>
#include <vector>
#include <stack>
#include <iostream>

namespace ariel{

enum iterator_type{PRE_ORDER, POST_ORDER, IN_ORDER};

template <typename T>
class BinaryTree{
    // class iterator; //declaretion for operator<<

private:
    struct Node{
    T data;
    Node* right;    
    Node* left;    

    Node(const T& data, Node* right=nullptr, Node* left=nullptr)
    :data(data), right(right), left(left){}
    
    Node(const Node& other): 
    data(other.data), right(other.right), left(other.left)
    {}
    };
    
    
Node* _head;
std::list<Node> container;
std::list<T> list_order;

public:
BinaryTree():
_head(nullptr){}

BinaryTree(const BinaryTree<T>& bt);/////to write!

~BinaryTree(){}//to write!!

/*
BinaryTree<T>& operator=(const BinaryTree<T>& bt){
    if(this==bt) return *this;
    while(!container.empty()){//delete all the old nodes of container. 
        Node* n = &(container.front());
        container.pop_front();
        delete n;
    }

}
*/
friend std::ostream& operator<< (std::ostream& os, BinaryTree<T> const &tree){
    os<<"BinaryTree:"<<endl;
    list<Node> list;
    // iterator(tree._head);
    const Node *p = tree._head;
    

    
    if(p) list.push_back(*p);
    while(!list.empty()){
        Node n = list.front();
        p = &n;
        list.pop_front();
        os<<"DATA: "<<p->data;
        
        if(p->left){
           os<<"  left: "<<p->left->data;
            list.push_back(*(p->left));
        }else{
           os<<"  left: "<<'-';
        }
        
        if(p->right){
           os<<"  right: "<<p->right->data;
            list.push_back(*(p->right));
        }else{
           os<<"  right: "<<'-';
        }
        os<<endl;
    }
    
    return os;
}


BinaryTree& add_root(const T& head);
BinaryTree& add_left(const T& father,const T& left);
BinaryTree& add_right(const T& father, const T& right);


private:
class iterator{
    Node* current_node;
    iterator_type type;
    stack<Node*> stack;
    
public:
    iterator(Node* ptr = nullptr, iterator_type it_type = IN_ORDER)
    :current_node(ptr),type(it_type) {
        
        if(type==iterator_type::IN_ORDER){
            while(current_node){
                stack.push(current_node);
                current_node = current_node->left;
            }
            current_node = stack.top();
        }
    }
    
    T& operator*()const//maybe return a T data.
    {
        return current_node->data;
    }

    T* operator->()const
    {
        return &current_node->data;
    }
    

    iterator& operator++(){ //++i
        if(type==iterator_type::PRE_ORDER){
        if(current_node->left) {
            stack.push(current_node);//for the right
            current_node = current_node->left;
        }else{
            if(stack.empty() || (!stack.top()->right)) { //empty or have no right
                this->current_node=nullptr;
                return *this;
            }
            Node right = *stack.top();
            stack.pop();
            if(right.right) current_node = right.right;
        }
        return *this;
        }
        if(type==iterator_type::IN_ORDER){
            Node* n = this->current_node;
            if(stack.empty) {
                current_node = nullptr;
                return *this;
            }
            if(current_node == stack.top()){
                
            }
        }
        return *this;
        
    }
    iterator& operator++(int){ //i++
        //the body of the order!
        iterator temp = *this;
        current_node = current_node->left;//here.
        return temp;
    }
    bool operator==(const iterator& other)const
    {
        return current_node == other.current_node;
    }

    bool operator!=(const iterator& other)const
    {
        return current_node != other.current_node;
    }
};//end class iterartor

Node* search(const T& searched, Node* current){
    if(current == nullptr) return nullptr;
    if(current->data == searched) return current;

    Node* result = search(searched, current->left);
    if(result != nullptr) return result; 
    result = search(searched, current->right);
    if(result != nullptr) return result; 
    return nullptr;
}

public:
iterator begin(){
    // inOrder ---- < | > ----
    return begin_inorder();
}
iterator end(){
    // inOrder ---- < | > ----
    return end_inorder();
}

iterator begin_preorder(){
    // ---- | < > ----
    return iterator(_head);
}

iterator end_preorder(){//to write.
    Node* temp = _head;
    if(temp != nullptr)
    while(temp->right != nullptr ){
        temp =  temp->right;
    }
    
    return iterator(nullptr);
}

iterator begin_inorder(){
    //  ---- < | > ----
    
    Node* p = _head;
    if(p!=nullptr)
    while(p->left != nullptr){
        p = p->left;
    }
    
    return iterator(_head);
}

iterator end_inorder(){
    return iterator(nullptr);
}

iterator begin_postorder(){
    //  ---- < > | ----
    return iterator(_head,iterator_type::POST_ORDER);
}

iterator end_postorder(){
    return iterator(nullptr);
}







};//end class BinaryTree


/////////////////////////////////////////// implements /////////////////////////

template<typename T> BinaryTree<T>& BinaryTree<T>::add_root(const T& head){
if(_head!=nullptr){
    _head->data = head;
    // _head = (new Node(head,_head->right,_head->left));
}else{
    _head = new Node(head);
}
return *this;
}

template<typename T> BinaryTree<T>& BinaryTree<T>::add_left(const T& father, const T& left){
    Node* p = search(father, _head);
    if(p==nullptr) { throw "this father is not in the Binary Tree";}
    if(p->left == nullptr){
        p->left = new Node(left);
    }else{
        p->left->data = left;
    }
    return *this;
}

template<typename T> BinaryTree<T>& BinaryTree<T>::add_right(const T& father, const T& right){
    Node* p = search(father, _head);
    if(p==nullptr) { throw "this father is not in the Binary Tree";}
    if(p->right == nullptr){
        p->right = new Node(right);
    }else{
        p->right->data = right;
    }
    return *this;
}




}
