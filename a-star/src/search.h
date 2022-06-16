#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>


#include "./problem.h"
#include "./node.h"

using namespace std;
typedef pair<node, int> pr;
class Search {
public:
  /**
   * @brief default constructor for Search
   */
  Search();
  
  /**
   * @brief Construct a new Search object
   *
   * @param p the Problem object to search
   */
  Search(const Problem& p);
  
  /**
   * @brief Construct a new Search object
   *
   * @param other the Search object to copy from
   */
  Search(const Search& other);
  
  /**
   * @brief assignment operator to assign RHS to the current Search object
   *
   * @param RHS the Search object to copy from
   * @return the current Search object that is a duplicate of RHS
   */
  Search& operator=(const Search& RHS);
  
  /**
   * @brief destructor to delete the current Search object
   */
  ~Search();
  
  /**
   * @brief a friend ostream operator to print the current state and goal state.
   *
   * @param outs ostream object to print the Search object.
   * @param s Search object to be printed.
   * @return std::ostream&, a reference to the original ostream object.
   */
  friend std::ostream& operator<<(std::ostream& outs, const Search& s) {
    outs << *s._problem << std::endl;
    return outs;
  }
  
  /**
   * @brief set member variable _problem to the \p p
   *
   * @param p the Problem object to instantiate  member variable \p _problem
   */
  void setProblem(const Problem& p);
  
  /**
   * @brief a function to search for the goal state
   *
   * @param p a Problem object to instantiate search
   * @return true if a goal state was found and false otherwise,
   */
  bool search(const Problem& p, HEURISTIC h = HEURISTIC::MISPLACED_TILES);
  
  /**
   * @brief a function to search for the goal state
   *
   * @return true if a goal state was found and false otherwise,
   */
  bool search(HEURISTIC h = HEURISTIC::MISPLACED_TILES);
  
  /**
   * @brief expand the priority queue with the available moves for node n
   * @param m a map to containing all the explored nodes so far
   * @param n the current node being expanded
   */
  void expand(std::map<Problem, std::string>& m, node* &n);
  
  std::vector<node> trace_path() const;
  
  void print_solution() const;
  
  void print_debug(const bool& debug = false) const;
private:
  
  bool contains(const std::map<Problem, std::string>& m, const Problem& p) const;
  
  bool contains(node n, const double& cost);
  
  /**
   * @brief the Problem object to search or solve
   */
  Problem* _problem;
  
  /**
   * @brief the the solution node of a search problem
   */
  node* _solution;
  
  /**
   * @brief a priority queue to store the nodes to be expanded
   */
  //  priority_queue<pr, std::vector<pr>, greater<std::vector<pr>::value_type>> __frontier;
  priority_queue<pr, std::vector<pr>, greater<pr>> __frontier;
  
  int explored_nodes;
  int items_in_frontier;
  int total_nodes_expanded;
};

Search::Search() {
  _problem = nullptr;
  _solution = nullptr;
  __frontier = {};
  explored_nodes = 0;
  items_in_frontier = 0;
  total_nodes_expanded = 0;
}

Search::Search(const Problem& p) {
  setProblem(p);
  _solution = nullptr;
  __frontier = {};
  explored_nodes = 0;
  items_in_frontier = 0;
  total_nodes_expanded = 0;
}

Search::Search(const Search& other) {
  _problem = other._problem;
  _solution = other._solution;
  __frontier = other.__frontier;
  explored_nodes = 0;
  items_in_frontier = 0;
  total_nodes_expanded = 0;
}

Search& Search::operator=(const Search& RHS) {
  if (this != &RHS) {
    _problem = RHS._problem;
    _solution = RHS._solution;
    __frontier = RHS.__frontier;
  }
  return *this;
}

Search::~Search() {
  _problem = nullptr;
  _solution = nullptr;
  __frontier = {};
}

void Search::setProblem(const Problem& p) {
  _problem = new Problem(p);
  _solution = nullptr;
  __frontier = {};
}

bool Search::search(const Problem& p, HEURISTIC h) {
  _problem = new Problem(p);
  return search();
}

bool Search::search(HEURISTIC h) {
  
  node* root = new node(*_problem, nullptr, h);
  node* current = nullptr;
  _solution = nullptr;
  __frontier = {};
  std::map<Problem, std::string> explored;
  pr temp;
  __frontier.push(make_pair(*root, root->get_path_cost()));
  items_in_frontier++;
  
  do {
    if (__frontier.empty()) {
      return false;
    }
    
    temp = __frontier.top();
    current = new node();
    *current = temp.first;
    __frontier.pop();
    items_in_frontier--;
    total_nodes_expanded++;
    
    if (current->_item.goal_test()) {  // return node;
      _solution = current;
      std::cout << *current << "        ... final node with f(n): "
      << current->get_path_cost() << std::endl << std::endl;
      return true;
    }
    explored[current->_item] = "explored";
    explored_nodes++;
    
    std::cout << *current << "        .... explored node with f(n): "
    << current->get_path_cost() << std::endl << std::endl;
    expand(explored, current);
  } while (!__frontier.empty());
  return false;
}

void Search::expand(std::map<Problem, std::string>& m, node* &n) {
  Move moves[] = {Move::UP, Move::DOWN, Move::LEFT, Move::RIGHT};
  node* child = nullptr;
  bool is_in_frontier = false;
  bool is_explored = false;
  bool valid = false;
  
  for (int i = 0; i < 4; i++) {
    valid = n->_item.move_is_valid(moves[i]);
    if(valid) {
      child = child_node(n->_item, n, moves[i]);
      is_explored = contains(m, child->_item);
      
      if (!is_explored) {
        is_in_frontier = contains(*child, child->get_path_cost());
        if(!is_in_frontier){
          __frontier.push(make_pair(*child, child->get_path_cost()));
          items_in_frontier++;
        }
      }
    }
  }
}

bool Search::contains(const std::map<Problem, std::string> &m, const Problem &p) const {
  for (auto it = m.begin(); it != m.end(); ++it) {
    if (it->first == p) {
      return true;
    }
  }
  return false;
}

bool Search::contains(node n, const double& cost) {
  //  priority_queue<pr, std::vector<pr>, greater<std::vector<pr>::value_type>> temp;
  //  priority_queue<pr, std::vector<pr>, greater<std::vector<pr>::value_type>> temp2;
  priority_queue<pr, std::vector<pr>, greater<pr>> temp;
  priority_queue<pr, std::vector<pr>, greater<pr>> temp2;
  
  bool found = false, replaced = false;
  pr current;
  temp = __frontier;
  temp2 = {};
  
  while (!temp.empty()) {
    current = temp.top();
    if(current.first._item == n._item) {
      found = true;
      if(current.second > n.get_path_cost()) {
        current.second = n.get_path_cost();
        current.first._parent = &n;
        replaced = true;
        
      }
    }
    temp2.push(current);
    temp.pop();
    if(replaced) break;
  }
  if (replaced) {
    __frontier = {};
    while(!temp.empty() || !temp2.empty()){
      if(!temp.empty()) {
        __frontier.push(temp.top());
        temp.pop();
      }
      if(!temp2.empty()) {
        __frontier.push(temp2.top());
        temp2.pop();
      }
    }
  }
  return found;
}

std::vector<node> Search::trace_path() const {
  std::vector<node> path;
  node* temp = _solution;
  path.push_back(*temp);
  while (temp->_parent != nullptr) {
    temp = (temp->_parent);
    path.push_back(*temp);
  }
  return path;
}

void Search::print_solution() const {
  print_debug(true);
  std::vector<node> path = trace_path();
  
  std::cout << "==============================================" << std::endl;
  for(auto it = path.crbegin(); it != path.crend(); ++it) {
    std::cout << *it << "       -----> f(n) =  " << it->get_path_cost() << "\n\n";
  }
}

void Search::print_debug(const bool& debug) const {
  if(debug) {
    std::cout << "===========================================================";
    std::cout << "                      debug info" << std::endl;
    std::cout << "total explored nodes: " << explored_nodes << std::endl;
    std::cout << "items in frontier:  " << items_in_frontier << std::endl;
    std::cout << "total queue size :  " << total_nodes_expanded << std::endl;
    
    std::cout << "------------------------------------------------------------";
    std::cout << std::endl << std::endl;
  }
}

#endif  // SEARCH_H
