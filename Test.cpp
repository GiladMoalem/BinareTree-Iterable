#include "doctest.h"
#include "BinaryTree.hpp"
#include <string>

using namespace std;
using namespace ariel;


TEST_CASE("first"){
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
TEST_CASE("first"){
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(10));
    CHECK_NOTHROW(tree.add_right(10,-3));
  
    CHECK_THROWS(tree.add_right(11,3));
    CHECK_NOTHROW(tree.add_left(11,-3));
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
TEST_CASE("string tree not same letters"){
    BinaryTree<string> str_tree;
    CHECK_THROWS(str_tree.add_root(0));
}