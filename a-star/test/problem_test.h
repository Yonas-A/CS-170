
#include <iostream>
#include <queue>

#include "./const.h"
#include "../src/problem.h"

using namespace std;

void test_problem_constructor() {
  Problem p;
  p.set_initial_state(puzzle);
  cout << p << endl;
}

void test_move() {
  Problem p(puzzle);
  cout << p << endl;
  
  for (size_t i = 0; i < 4; i++) {
    p.move(Move::DOWN);
    cout << "move down  " << p << endl;
  }
  
  for (size_t i = 0; i < 4; i++) {
    p.move(Move::LEFT);
    cout << "move left  " << p << endl;
  }
  
  for (size_t i = 0; i < 4; i++) {
    p.move(Move::UP);
    cout << "move up  " << p << endl;
  }
  
  for (size_t i = 0; i < 4; i++) {
    p.move(Move::RIGHT);
    cout << "move right  " << p << endl;
  }
}

void test_empty_v_cell() {
  Problem p(puzzle);
  cout << p << endl;
  
  p.print_empty();
  int row, col;
  p.find_empty_cell(row, col);
  cout << "_NEW_ :: row : " << row << "    col: " << col << endl << endl;
  
  p.move(Move::DOWN);
  p.move(Move::DOWN);
  p.move(Move::DOWN);
  cout << p << endl;
  p.print_empty();
  p.find_empty_cell(row, col);
  cout << "_NEW_ :: row : " << row << "    col: " << col << endl << endl;

  p.move(Move::RIGHT);
  p.move(Move::RIGHT);
  p.move(Move::RIGHT);

  cout << p << endl;
  p.print_empty();
  p.find_empty_cell(row, col);
  cout << "_NEW_ :: row : " << row << "  col: " << col << endl << endl;

    
  p.move(Move::LEFT);
  cout << p << endl;
  p.print_empty();
  p.find_empty_cell(row, col);
  cout << "_NEW_ :: row : " << row << "  col: " << col << endl << endl;
  
  p.move(Move::LEFT);
  p.move(Move::UP);
  cout << p << endl;
  p.print_empty();
  p.find_empty_cell(row, col);
  cout << "_NEW_ :: row : " << row << "  col: " << col << endl << endl;

  p.move(Move::UP);
  cout << p << endl;
  p.print_empty();
  p.find_empty_cell(row, col);
  cout << "_NEW_ :: row : " << row << "  col: " << col << endl << endl;
}

void test_cost() {
  Problem p(puzzle);
  cout << p << endl;
  
  int row, col;
  int row_goal, col_goal;
  p.find_target_from_initial(2, row, col);
  p.find_target_from_goal(2, row_goal, col_goal);

  
  cout << "misplaced tiles:     " << p.misplaced_tiles_count() << endl;
  cout << "euclidean distance:  " << p.euclidean_distance(2) << endl;
  cout << "euclidean distance:  " << p.euclidean_distance() << endl;
  
  Problem n(doable);
  cout << n << endl;
  
  cout << "misplaced tiles:     " << n.misplaced_tiles_count() << endl;
  cout << "euclidean distance:  " << n.euclidean_distance(2) << endl;
  cout << "euclidean distance:  " << n.euclidean_distance() << endl;
}

void test_problem_queue() {
  Problem p1(puzzle);
  
  Problem p2(puzzle2);
  p2.move(Move::LEFT);
  
  Problem p3(puzzle3);
  p3.move(Move::RIGHT);
  p3.move(Move::DOWN);
  
  // priority_queue<Problem, vector<Problem>, less<vector<Problem>::value_type>> pq;
  priority_queue<Problem, vector<Problem>, greater<vector<Problem>::value_type>> pq;
  
  pq.push(p1);
  pq.push(p2);
  pq.push(p3);
  
  // iterate, display and pop
  
  while (!pq.empty()) {
    Problem value = pq.top();
    cout << value << " : " << value.misplaced_tiles_count() << endl;
    pq.pop();
  }
}
