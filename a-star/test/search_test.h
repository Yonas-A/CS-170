#include <iostream>
#include <queue>

#include "./const.h"
#include "../src/problem.h"
#include "../src/search.h"

using namespace std;

void Make_p(const Problem& p) {
  Problem m = p;
  cout << m << endl;
}

void simple_test() {
  Problem p(puzzle);
  cout << p << endl;

  Problem m = p;
  cout << m << endl;

  Make_p(p);
}

void test_search_problem() {
  Problem p(puzzle);
  Search s;
  s.setProblem(p);
  cout << std::boolalpha ;
  cout << s.search() << s << endl;

}

void test_search_() {
  Problem p(puzzle);
  Search s(p);
  if(s.search())
    cout << s << endl;
  cout << "---------------------------------------" << endl;
  
  p.set_initial_state(puzzle2);
  s.setProblem(p);
  if(s.search())
    cout << s << endl;
  cout << "---------------------------------------" << endl;
  
  p.set_initial_state(puzzle3);
  s.setProblem(p);
  if(s.search())
    cout << s << endl;
  cout << "---------------------------------------" << endl;
  
  p.set_initial_state(puzzle4);
  s.setProblem(p);
  if(s.search())
    cout << s << endl;
  cout << "---------------------------------------" << endl;
}

void test() {
  std::map<Problem, std::string> explored;
  Problem p(puzzle);
  Problem s(puzzle2);

  cout << p << endl;
  cout << s << endl;

  for(int i = 0; i < 3; i++) {
    if(explored.find(p) == explored.end())
      explored[p] = "p";
  }
  explored[p] = "p";
  explored[s] = "s";

  cout << "explored[p]: " << explored[p] << endl;

  if(explored.count(p))  {
    cout << "found";
  }
}

void test_node_search() {
  bool found = false;
  Problem p(impossible);
  Search s(p);
  
  found = s.search();
  if(found)
    s.print_solution();
  else
    cout << "failed" << endl;
}

void test_hard() {
  bool found = false;
  Problem p(hardPuzzle);
  Search s(p);
  
  found = s.search();
  if(found)
    s.print_solution();
  else
    cout << "failed" << endl;
}
