#include <iostream>

#include "./const.h"
#include "../src/node.h"
#include "../src/problem.h"

using namespace std;

void test_node() {
  Problem p(puzzle);
  cout << p << endl;

  node n(p);
  cout << n << endl;
}

void test_add_node() {
  Problem p(puzzle);
  node root(p);
//  cout << root << endl;

  root.add_child(Move::LEFT);
  root.add_child(Move::DOWN);
  root.print_child();
  
}

void test_child_node() {
  Problem p(puzzle);
  //  cout << p << endl;
  
  node root(p);
  //  cout << parent << endl;
  
  node* new_node = nullptr;
  new_node = child_node(p, &root, Move::LEFT);
  cout << *new_node;
  
  node* temp = new_node;
  while(temp != nullptr){
    cout << temp->_item;
    temp = temp->_parent;
  }
  
  
}

