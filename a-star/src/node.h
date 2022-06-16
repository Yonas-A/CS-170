#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

#include "./problem.h"

/**
 * @brief an enum to distinguish between what search algorithm or heuristic to use
 */
enum class HEURISTIC {UNIFORM_COST, MISPLACED_TILES, EUCLIDEAN};

const int STEP_COST = 1;
/**
 * @brief a node structure that  keeps track of the current Problem state,
 * the parent state, the children of the current problem, the action that
 * gave the current state and path cost of the current problem
 */
struct node {
  /**
   * @brief Construct a new node object
   *
   * @param p the state of the current node
   * @param parent the parent node of the current node
   */
  node(const Problem& p = Problem(), node* parent = nullptr, HEURISTIC h = HEURISTIC());

  /**
   * @brief get the current \p _item of current node
   *
   * @return a Problem object that is a copy of the current node
   */
  Problem get_state() const;
    
  void set_heuristic(const HEURISTIC& h = HEURISTIC::EUCLIDEAN);

  float get_heuristic() const;
  
  /**
   * @brief get the f(n) of the current \p node
   *
   * @return the estimated cost of the cheapest solution through this node
   */
  float get_path_cost() const;
  
  /**
   * @brief an ostream insertion operator to print the state of the node i.e
   * the \p Problem object
   *
   * @param outs an ostream operator
   * @param n the node object to print
   * @return std::ostream& the stream to be printed
   */
  friend std::ostream& operator<<(std::ostream& outs, const node& n);
  
  /**
   * @brief a comparison operator to compare two node objects based on the
   * heuristic function of f(n) = g(n) + h(n)
   *
   * @param lhs the left hand side node object
   * @param rhs the right hand side node object
   * @return true if lhs is greater than rhs
   */
  friend bool operator>(const node& lhs, const node& rhs) {
    return lhs._path_cost + lhs._h_cost < rhs._path_cost + lhs._h_cost ;
  }
  
  /**
   * @brief a comparison operator to compare two node objects based on the
   * heuristic function of f(n) = g(n) + h(n)
   *
   * @param lhs the left hand side node object
   * @param rhs the right hand side node object
   * @return true if lhs is greater than rhs
   */
  friend bool operator<(const node& lhs, const node& rhs) {
    return lhs._path_cost + lhs._h_cost < rhs._path_cost + lhs._h_cost ;
  }
  
  /**
   * @brief the data of the node
   */
  Problem _item;
  
  /**
   * @brief the parent node of the current node
   */
  node* _parent;
  
  /**
   * @brief action that was applied to the parent to generate this node
   */
  Move _action;
  
  /**
   * @brief the path from the initial state to the current \p node i.e g(n)
   */
  double _path_cost;
  
  /**
   * @brief the path from the current \p node to goal  state i.e h(n)
   */
  double _h_cost;
  
  /**
   * @brief the depth of the current node from the parent \p node
   */
  int _depth;
  
  HEURISTIC _h;
};

node::node(const Problem& p, node* n, HEURISTIC h) {
  _parent = n;
  _item = p;
  _action = Move();
  _path_cost = 0;
  _depth = 0;
  _h = h;
  set_heuristic(h);
}

Problem node::get_state() const {
  return _item;
}

float node::get_heuristic() const {
  return _h_cost;
}

void node::set_heuristic(const HEURISTIC &h) {
  if (h == HEURISTIC::UNIFORM_COST) _h_cost = 0;
  else if (h == HEURISTIC::MISPLACED_TILES) _h_cost = _item.misplaced_tiles_count();
  else _h_cost = _item.euclidean_distance();
}

float node::get_path_cost() const {
  return _path_cost + _h_cost;
}

std::ostream& operator<<(std::ostream& outs, const node& n) {
//  outs << n._item << std::endl;
  outs << n._item;
  return outs;
}

// ----------------------------------------------------------------------------
/**
 * @brief generate a child node from a parent node and an action
 * @note the step cost for a single action (move) is taken as 1
 *
 * @param p the problem to generate the child node from
 * @param n the parent node to generate the child node from
 * @param action the action to be applied to \p parent to generate the child node
 * @return node* the child node generated by the action
 */
node* child_node(const Problem& p, node* &n, Move action) {
  node* child = new node(p, n);
  child->_item.move(action);
  child->_action = action;
  child->_path_cost = n->_path_cost + STEP_COST;
  child->set_heuristic(n->_h); // sets the _h_cost
  child->_depth = n->_depth + 1;
  child->_h = n->_h;
  return child;
}

#endif  // NODE_H