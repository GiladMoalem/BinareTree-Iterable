#include "doctest.h"
#include "BinaryTree.hpp"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <vector>
#include <map>
#include <assert.h>


using namespace std;
using namespace ariel;

void inOrderRec(const map<int,int>& right, const map<int,int>& left, int current, vector<int>& orderList){
    if(left.find(current) != left.end())  
            inOrderRec(right, left, left.at(current), orderList);
    
    orderList.push_back(current);

    if(right.find(current) != right.end())
            inOrderRec(right, left, right.at(current), orderList);
}

void postOrderRec(const map<int,int>& right, const map<int,int>& left, int current, vector<int>& orderList){
    if(left.find(current) != left.end())  
            postOrderRec(right, left, left.at(current), orderList);
    
    if(right.find(current) != right.end())
            postOrderRec(right, left, right.at(current), orderList);

    orderList.push_back(current);
}
void preOrderRec(const map<int,int>& right, const map<int,int>& left, int current, vector<int>& orderList){
    orderList.push_back(current);
    
    if(left.find(current) != left.end())  
            preOrderRec(right, left, left.at(current), orderList);
    
    if(right.find(current) != right.end())
            preOrderRec(right, left, right.at(current), orderList);
}

BinaryTree<int>& creat_tree(BinaryTree<int>& tree){
    //////////////////
    //      1       //
    //    /   \     // 
    //   2     3    //
    //  / \   / \   //
    // 4   5 6   7  //
    //////////////////
    tree.add_root(1)
    .add_left(1,2)
    .add_right(1,3)
    .add_left(2,4)
    .add_right(2,5)
    .add_left(3,6)
    .add_right(3,7);
return tree;
}

TEST_CASE("all functions works"){
    BinaryTree<int> tree;
    CHECK_NOTHROW(cout<<tree<<endl);
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(tree.add_right(1,2));
    CHECK_NOTHROW(tree.add_left(1,3));
    CHECK_NOTHROW(tree.begin());
    CHECK_NOTHROW(tree.begin_inorder());
    CHECK_NOTHROW(tree.begin_postorder());
    CHECK_NOTHROW(tree.begin_preorder());
    CHECK_NOTHROW(tree.end());
    CHECK_NOTHROW(tree.end_inorder());
    CHECK_NOTHROW(tree.end_postorder());
    CHECK_NOTHROW(tree.end_preorder());
}
TEST_CASE("basic build tree - added '3' node two times and adds for one of them '567' node"){
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(3));
    CHECK_NOTHROW(tree.add_left(3,4));
    CHECK_NOTHROW(tree.add_left(4,5));
    CHECK_NOTHROW(tree.add_right(3,2));
    CHECK_NOTHROW(tree.add_right(2,1));
    CHECK_NOTHROW(tree.add_root(3));

    CHECK_NOTHROW(tree.add_right(1,3));
    CHECK_NOTHROW(tree.add_right(3,567));
}
TEST_CASE("add for not declar node"){
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(10));
    CHECK_NOTHROW(tree.add_right(10,-3));
  
    CHECK_THROWS(tree.add_right(11,3));
    CHECK_THROWS(tree.add_left(11,-3));
}
TEST_CASE("no root checking"){
    BinaryTree<int> tree;
    CHECK_THROWS(tree.add_left(3,2));
    CHECK_THROWS(tree.add_right(3,2));

    BinaryTree<string> str_tree;
    CHECK_THROWS(str_tree.add_left("","Gilad"));
    CHECK_THROWS(str_tree.add_right("","Sapir"));
}

TEST_CASE("string tree not same letters"){
    BinaryTree<string> str_tree;
    CHECK_NOTHROW(str_tree.add_root("root"));
    CHECK_NOTHROW(str_tree.add_root("Root"));
   
    CHECK_NOTHROW(str_tree.add_left("Root","Gilad"));
    CHECK_THROWS(str_tree.add_left("root","Gilad"));
   
    CHECK_NOTHROW(str_tree.add_right("Root","Sapir"));
    CHECK_THROWS(str_tree.add_right("root","Sapir"));
}
TEST_CASE("replace root"){
    BinaryTree<int> tree;
    CHECK_NOTHROW( tree.add_root(3));
    CHECK_NOTHROW( tree.add_root(5));
    
    auto it = tree.begin_inorder();
    CHECK_EQ(*it, 5);
    it = tree.begin_postorder();
    CHECK_EQ(*it, 5);
    it = tree.begin_preorder();
    CHECK_EQ(*it, 5);
    it = tree.begin();
    CHECK_EQ(*it, 5);

    CHECK_THROWS(tree.add_right(3,7));
    CHECK_THROWS(tree.add_left(3,7));
}

TEST_CASE("repalce root and children remain in place"){
    //    1    //
    //  /   \  //
    // 2     3 //
    /// \      //
    BinaryTree<int> tree;
    tree = creat_tree(tree);

    CHECK_NOTHROW(tree.add_root(10));
    
    auto it = tree.begin_preorder();
    CHECK_EQ(*it,10);
    it++;
    CHECK_EQ(*it,2);
    it++; //4
    it++; //5
    it++; //3
    CHECK_EQ(*it,3);
}
TEST_CASE("repalce spacific node(not root) and children remain in place"){
    BinaryTree<int> tree;
    tree = creat_tree(tree);
    CHECK_NOTHROW(tree.add_left(1,-2));
    
    auto it = tree.begin_preorder();
    it++;
    CHECK_EQ(*it, -2);
    it++;
    CHECK_EQ(*it, 4);
    it++;
    CHECK_EQ(*it, 5);
}
TEST_CASE("basic orders checking"){
    BinaryTree<int> tree = creat_tree(tree);
    list<int> pre_list  {1,2,4,5,3,6,7};
    list<int> in_list   {4,2,5,1,6,3,7};
    list<int> post_list {4,5,2,6,7,3,1};

    list<int>::iterator list_itr;
    // pre
    list_itr = pre_list.begin();
    for(auto it = tree.begin_preorder(); it!=tree.end_preorder(); list_itr++, it++){
        CHECK_EQ(*it, *list_itr);
    }
    //in 
    list_itr = in_list.begin();
    for(auto it = tree.begin_inorder(); it!=tree.end_inorder(); list_itr++, it++ ){
        CHECK_EQ(*it, *list_itr);
    }
    // post
    list_itr = post_list.begin();
    for(auto it = tree.begin_postorder();it!=tree.end_postorder();list_itr++,it++ ){
        CHECK_EQ(*it, *list_itr);
    }

    list_itr = in_list.begin();
    for(int n:tree){
        CHECK_EQ(n, *list_itr);
        list_itr++;
    }
}
TEST_CASE("string tree"){
    BinaryTree<string> tree;
    tree.add_root("Father")
        .add_left("Father", "Gilad")
        .add_right("Father", "Itamar")
        .add_left("Itamar", "Liam")
        .add_right("Itamar", "Moral");
    ////////////////////////////////
    //          Father            //
    //    Gilad        Itamar     //
    //  -      -     Liam  Moral  //
    ////////////////////////////////
    ostringstream preSS;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder() ; it++)
    {
        preSS <<*it<<' ';
    }
    CHECK_EQ(preSS.str(),"Father Gilad Itamar Liam Moral " );
    
    

}
TEST_CASE("creating big random int tree"){
    BinaryTree<int> tree;
    set<int> contains; // all the data nodes.
    map<int, int> rights;
    map<int, int> lefts;
    set<int>::iterator itr_contains;
    srand (time(NULL));

    
    int dataNode = rand() % 1000 +1; // 1 - 1000
    int root = dataNode;
    
    tree.add_root(dataNode);
    contains.insert(dataNode);

for(int times=0; times<500;times++){

// rand node from contains list.
    itr_contains = contains.begin();
    for(int i=0; i < (rand() % (int)(contains.size()) ) ;i++){
        itr_contains++;
    }
    dataNode = *itr_contains;
    
// rand node that - not in - contains list.
    int newDataNode;
    while( contains.find( newDataNode)!=contains.end() ){newDataNode = rand() % 1000 +1; }
    
    int side = rand() % 2; // 0 left | 1 right
    if(side){ //right
        
        if(rights.find(dataNode) != rights.end() ){// to update excist node
            contains.erase(rights[dataNode]);
            if(rights.find(rights[dataNode]) != rights.end()  ){// the old node have right child
                rights[newDataNode] = rights[rights[dataNode]];
                rights.erase(rights[dataNode]);
            }
            if(lefts.find(rights[dataNode]) != lefts.end()  ){// the old node have left child
                lefts[newDataNode] = lefts[rights[dataNode]];
                lefts.erase(rights[dataNode]);
            }
        }
        CHECK_NOTHROW( tree.add_right(dataNode, newDataNode)) ;
        rights[dataNode] = newDataNode;
        contains.insert(newDataNode);
        
    }else{ //left
        if(lefts.find(dataNode) != lefts.end()){
            contains.erase(lefts[dataNode]);
            if(rights.find(lefts[dataNode]) != rights.end() ){
                rights[newDataNode] = rights[lefts[dataNode]];
                rights.erase(lefts[dataNode]);
            }
            if(lefts.find(lefts[dataNode]) != lefts.end()){
                lefts[newDataNode] = lefts[lefts[dataNode]];
                lefts.erase(lefts[dataNode]);
            }
        }
        CHECK_NOTHROW( tree.add_left(dataNode, newDataNode));
        lefts[dataNode] = newDataNode;
        contains.insert(newDataNode);
    }
}//times for
vector<int> preOrder;
preOrderRec(rights, lefts, root, preOrder);

vector<int>::iterator preIter = preOrder.begin();
for(auto it = tree.begin_preorder(); it!=tree.end_preorder(); preIter++, it++){
    CHECK_EQ(*it, *preIter);
} 
CHECK_EQ(preIter, preOrder.end());

vector<int> postOrder;
vector<int>::iterator postIter;
postOrderRec(rights, lefts, root, postOrder);
for(auto it = tree.begin_postorder(); it!=tree.end_postorder(); postIter++, it++){
        CHECK_EQ(*it, *postIter);
} 
CHECK_EQ(postIter, postOrder.end());


vector<int> inOrder;
vector<int>::iterator inIter;
inOrderRec(rights, lefts, root, inOrder);
for(auto it = tree.begin_inorder(); it!=tree.end_inorder(); inIter++, it++){
    CHECK_EQ(*it, *inIter);
} 
CHECK_EQ(inIter, inOrder.end());


}

