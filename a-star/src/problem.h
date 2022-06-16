#ifndef PROBLEM_H
#define PROBLEM_H

#include <math.h>

#include <iostream>

const int PROBLEM_ROW = 3;
const int PROBLEM_COL = 3;

enum class Move { UP, DOWN, LEFT, RIGHT };

class Problem {
 public:
  /**
   * @brief Construct a new Problem object without any initial state
   *
   */
  Problem();

  /**
   * @brief Construct a new Problem object
   *
   * @param puzzle a two-dimensional array of integers representing the puzzle
   */
  Problem(int puzzle[PROBLEM_ROW][PROBLEM_COL]);

  /**
   * @brief Construct a new Problem object
   *
   * @param other the other Problem object to copy from
   */
  Problem(const Problem& other);

  /**
   * @brief assignment operator to assign RHS to the current problem object
   *
   * @param RHS the other Problem object to copy from
   * @return the current Problem object that is a duplicate of RHS
   */
  Problem& operator=(const Problem& RHS);

  /**
   * @brief destructor to delete the current Problem object
   */
  ~Problem();

  /**
   * @brief set the initial state of the problem to from puzzle
   * @param puzzle a two-dimensional array of integers representing the puzzle
   */
  void set_initial_state(int puzzle[][PROBLEM_COL]);

  // =============================================================================

  /**
   * @brief a friend ostream operator to print the current state and goal state
   *
   * @param outs ostream object to print the Problem object
   * @param p Problem object to print
   * @return std::ostream&
   */
  friend std::ostream& operator<<(std::ostream& outs, const Problem& p) {
//    outs << std::endl;
    p.print(p.initial_state, outs);
    return outs;
  }

  /**
   * @brief a comparison operator to compare two problem objects based on the
   * heuristic function of f(n) = g(n) + h(n)
   *
   * @param lhs the left hand side Problem object
   * @param rhs the right hand side Problem object
   * @return true if lhs is less than rhs
   */
  friend bool operator<(const Problem& lhs, const Problem& rhs) {
    return lhs.misplaced_tiles_count() < rhs.misplaced_tiles_count();
  }

  /**
   * @brief a comparison operator to compare two problem objects based on the
   * heuristic function of f(n) = g(n) + h(n)
   *
   * @param lhs the left hand side Problem object
   * @param rhs the right hand side Problem object
   * @return true if lhs is greater than rhs
   */
  friend bool operator>(const Problem& lhs, const Problem& rhs) {
    return lhs.misplaced_tiles_count() > rhs.misplaced_tiles_count();
  }

  /**
   * @brief a comparison operator to compare two problem objects based on the
   * their initial state
   *
   * @param lhs the left hand side Problem object
   * @param rhs the right hand side Problem object
   * @return true if lhs is  equal to rhs
   */
  friend bool operator==(const Problem& lhs, const Problem& rhs) {
    return lhs.compare(lhs.initial_state, rhs.initial_state);
  }

  /**
   * @brief a comparison operator to compare two problem objects based on the
   * their initial state
   *
   * @param lhs the left hand side Problem object
   * @param rhs the right hand side Problem object
   * @return true if lhs is not equal to rhs
   */
  friend bool operator!=(const Problem& lhs, const Problem& rhs) {
    return lhs.compare(lhs.initial_state, rhs.initial_state);
  }

  // =============================================================================

  /**
   * @brief check if the current state is the goal state
   *
   * @return true if the current state is the goal state and false otherwise
   */
  bool goal_test() const;

  /**
   * @brief move the empty cell in initial_state a block in the direction of
   * \p move i.e \p Move::UP, \p Move::DOWN, \p Move::LEFT,
   * \p Move::RIGHT,
   *
   * @param m the direction of the move
   * @return true if the move is valid and false otherwise
   */
  bool move(Move m);
  
  /**
   * @brief find the position of the target in the initial_state and return
   * the row and column of the target as a reference to a pair of integers.
   *
   * @param target the target to find
   * @param row the row of the target
   * @param col the column of the target
   */
  void find_target_from_initial(const int& target, int& row, int& col) const;

  /**
   * @brief find the position of the target in the goal_state and return
   * the row and column of the target as a reference to a pair of integers.
   *
   * @param target the target to find
   * @param row the row of the target in goal_state
   * @param col the column of the target in goal_state
   */
  void find_target_from_goal(const int& target, int& row, int& col) const;

  /**
   * @brief count the number of entries that are not in their natural postion
   *
   * @return int the number of entries in initial_state that differ from
   * goal_state
   */
  int misplaced_tiles_count() const;

  /**
   * @brief find the euclidean distance heuristic of target
   *
   * \details  h(n) = sqrt((n.x-goal.x)^2 + (n.y-goal.y)^2)
   * @param target the target to find
   * @return find the euclidean distance heuristic of target
   */
  float euclidean_distance(const int& target) const;
  
  /**
   * @brief find the euclidean distance heuristic of the current state
   *
   * \details  h(n) = sqrt((n.x-goal.x)^2 + (n.y-goal.y)^2)
   * \note sqrt is omitted because it's quite a costly operation
   * @return the euclidean distance of the all the misplaced tiles
   */
  float euclidean_distance() const;
  
  /**
   * @brief Get the row object of the current state
   *
   * @return int the row where the empty cell is in \p initial_state
   */
  int get_row() const;
  
  /**
   * @brief Get the col object of the empty cell in the current state
   *
   * @return int the col where the empty cell is in \p initial_state
   */
  int get_col() const;
  
  /**
   * @brief find the empty space in the array (position of 0) and return the row
   *  and column
   */
  void find_empty_cell(int& row, int& col) const;
 
  void print_empty() {
    std::cout << "EMPTY :: row : " << empty_row << "   col: " << empty_col << std::endl;
  }

  /**
   * @brief check if a move is valid.
   *
   * @param move the direction of the move.
   * @return true if the move is valid and false otherwise.
   */
  bool move_is_valid(Move move) const;
  
 private:
  /**
   * @brief set the goal state of the problem
   */
  void set_goal_state();

  /**
   * @brief copy the initial state of the problem to current state
   * @param src the source array
   * @param dst the destination array
   */
  void copy(const int src[][PROBLEM_COL], int dst[][PROBLEM_COL]);
  /**
   * @brief compare the initial state of the two arrays to check for comparison
   * of two Problem objects
   *
   * @param lhs the first array to compare
   * @param rhs the second array to compare
   */
  bool compare(const int lhs[][PROBLEM_COL], const int rhs[][PROBLEM_COL]) const;


  
  /**
   * @brief print the array to screen
   * @param arr the array to print
   */
  void print(const int arr[][PROBLEM_COL], std::ostream& outs = std::cout) const;
  
  // =============================================================================
  //                        public member variables
  // =============================================================================
  /**
   * @brief the initial state of the problem
   */
  int initial_state[PROBLEM_COL][PROBLEM_COL];

  /**
   * @brief the goal state of the problem
   */
  int goal_state[PROBLEM_COL][PROBLEM_COL];

  /**
   * @brief list of all single atomic actions that transforms one state into
   * another
   */
  Move operators[4] = {Move::UP, Move::DOWN, Move::LEFT, Move::RIGHT};

  /**
   * @brief the row where empty cell is located in the \p initial_state
   */
  int empty_row;

  /**
   * @brief the col where empty cell is located in the \p initial_state
   */
  int empty_col;
};

// =============================================================================
//  function implementations
// =============================================================================

Problem::Problem() {
  set_goal_state();
}

Problem::Problem(int puzzle[][PROBLEM_COL]) {
  set_initial_state(puzzle);
  set_goal_state();
}

Problem::Problem(const Problem& other) {
  copy(other.initial_state, this->initial_state);
  copy(other.goal_state, this->goal_state);
  empty_row = other.empty_row;
  empty_col = other.empty_col;
}

Problem& Problem::operator=(const Problem& RHS) {
  if (this != &RHS) {  // check if self and RHS are the same object
    copy(RHS.initial_state, this->initial_state);
    copy(RHS.goal_state, this->goal_state);
    empty_row = RHS.empty_row;
    empty_col = RHS.empty_col;
  }
  return *this;
}

Problem::~Problem() {
  // delete initial_state;
  // delete goal_state;
}

// =============================================================================
//                        public member functions
// =============================================================================

void Problem::set_initial_state(int puzzle[][PROBLEM_COL]) {
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      if (puzzle[i][j] == 0) {
        empty_row = i;
        empty_col = j;
      }
      initial_state[i][j] = puzzle[i][j];
    }
  }
}

bool Problem::goal_test() const {
  for (int i = 0; i < PROBLEM_COL; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      if (initial_state[i][j] != goal_state[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool Problem::move(Move m) {
  int i = 0, j = 0;
  bool valid = move_is_valid(m);
  if (valid) {
    if (m == Move::UP)
      i = -1;
    else if (m == Move::DOWN)
      i = 1;
    else if (m == Move::LEFT)
      j = -1;
    else
      j = 1;
  }
  int temp = initial_state[empty_row][empty_col];
  initial_state[empty_row][empty_col] = initial_state[empty_row + i][empty_col + j];
  initial_state[empty_row + i][empty_col + j] = temp;
  
  empty_row += i;
  empty_col += j;
  return valid;
}

void Problem::find_target_from_initial(const int& target, int& row, int& col) const {
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      if (initial_state[i][j] == target) {
        row = i;
        col = j;
        return;
      }
    }
  }
}

void Problem::find_target_from_goal(const int& target, int& row, int& col) const {
//  assert(target && "target is 0");
  if (target == 0) {
    row = col = PROBLEM_COL - 1;
    return;
  }
  row = (target - 1) / PROBLEM_COL;
  col = (target - 1) % PROBLEM_COL;
}

int Problem::misplaced_tiles_count() const {
  int count = 0;
  int goal;
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      goal = goal_state[i][j];
      if (initial_state[i][j] != goal && goal != 0) {
        count++;
      }
    }
  }
  return count;
}

float Problem::euclidean_distance(const int& target) const {
  int row, col;
  int row_goal, col_goal;
  find_target_from_initial(target, row, col);
  find_target_from_goal(target, row_goal, col_goal);
  return pow(row - row_goal, 2) + pow(col - col_goal, 2);
}

float Problem::euclidean_distance() const {
  float count = 0;
  int goal, value;
  int row, col;
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      value = initial_state[i][j];
      goal = goal_state[i][j];
      if (value != goal && value != 0) {
        find_target_from_goal(value, row, col);
        count += pow(row - i, 2) + pow(col - j, 2);
      }
    }
  }
  return count;
}

int Problem::get_row() const {
  return empty_row;
}

int Problem::get_col() const {
  return empty_col;
}

void Problem::find_empty_cell(int& row, int& col) const {
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      if (initial_state[i][j] == 0) {
        row = i;
        col = j;
        return;
      }
    }
  }
}

// =============================================================================
// --------------            private functions                    --------------
// =============================================================================

void Problem::set_goal_state() {
  int count = 1;
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      goal_state[i][j] = count++;
    }
  }
  goal_state[PROBLEM_ROW - 1][PROBLEM_COL - 1] = 0;
}

void Problem::copy(const int src[][PROBLEM_COL], int dst[][PROBLEM_COL]) {
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      dst[i][j] = src[i][j];
    }
  }
}

bool Problem::compare(const int lhs[][PROBLEM_COL], const int rhs[][PROBLEM_COL]) const {
  for (int i = 0; i < PROBLEM_COL; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      if (lhs[i][j] != rhs[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool Problem::move_is_valid(Move move) const {
  switch (move) {
    case Move::UP:
      return (empty_row > 0);  // return true if the empty cell is not in the top row
    case Move::DOWN:
      return (empty_row < PROBLEM_ROW - 1);  // return true if the empty cell is not in the bottom row
    case Move::LEFT:
      return (empty_col > 0);  // return true if not at the leftmost column
    case Move::RIGHT:
      return (empty_col < PROBLEM_COL - 1);  // return true if not at the rightmost column
    default:
      return false;
  }
}

void Problem::print(const int arr[][PROBLEM_COL], std::ostream& outs) const {
  for (int i = 0; i < PROBLEM_ROW; i++) {
    for (int j = 0; j < PROBLEM_COL; j++) {
      if(arr[i][j] == 0)
        outs << "* ";
      else
        outs << arr[i][j] << " ";
    }
    outs << '\n';
  }
}

#endif  // PROBLEM_H
