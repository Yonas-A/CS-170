#ifndef SEARCH_INTERFACE_H
#define SEARCH_INTERFACE_H
#include <iostream>

#include "../src/node.h"
#include "../src/problem.h"
#include "../src/search.h"

using namespace std;


int doable[PROBLEM_ROW][PROBLEM_COL] = {
  {0, 1, 2},
  {4, 5, 3},
  {7, 8, 6}};

void display_menu() {
  cout << "[ P ]reloaded puzzle OR  [ I ]nsert puzzle [ Q ] uit:  ";
}

int display_algorithm_choice() {
  int choice = int();
  cout << "[1] UNIFORM COST     [2] MISPLACED_TILES     [3] EUCLIDEAN:    ";
  cin >> choice;
  return choice;
}

void insert_puzzle(int arr[][PROBLEM_COL]) {
  cout << "\nEnter puzzle, use a '0' to represent the blank.\n";
  cout << "use space or tabs or ENTER to separate numbers \n \n";
  
  int input;
  for (int i = 0; i < PROBLEM_ROW; i++)  {
    for (int j = 0; j < PROBLEM_COL; j++) {
      std::cin >> input;
      arr[i][j] = input;
    }
  }
}


void default_puzzle() {
  int choice = display_algorithm_choice();
  HEURISTIC h = HEURISTIC();
  if (choice == 1) h = HEURISTIC::UNIFORM_COST;
  else if (choice == 2) h = HEURISTIC::MISPLACED_TILES;
  else h = HEURISTIC::EUCLIDEAN;
  
  
  bool found = false;
  Problem p(doable);
  Search s(p);
  
  cout << "===================================================================" << endl;
  cout << "                   preloaded puzzle" << endl;
  cout << endl << p << endl;
  cout << "===================================================================" << endl;
  
  
  
  found = s.search(h);
  if(found) {
    cout << "===================================================================" << endl;
    cout << "                          solution"  << endl;
    s.print_solution();
    cout << endl << "===================================================================" << endl;
  }
  else {
    cout << "===================================================================" << endl;
    cout << "                 **         search failed       ** " << endl;
    cout << "===================================================================" << endl;
  }
}

void user_puzzle(int arr[PROBLEM_ROW][PROBLEM_COL]) {
  int choice = display_algorithm_choice();
  
  HEURISTIC h = HEURISTIC();
  if (choice == 1) h = HEURISTIC::UNIFORM_COST;
  else if (choice == 2) h = HEURISTIC::MISPLACED_TILES;
  else h = HEURISTIC::EUCLIDEAN;
  
  bool found = false;
  Problem p(arr);
  Search s(p);
  
  found = s.search(h);
  
  if(found) {
    cout << "===================================================================" << endl;
    cout << "                          solution"  << endl;
    s.print_solution();
    cout << endl << "===================================================================" << endl;
  }
  else {
    cout << "===================================================================" << endl;
    cout << "                 **         search failed       ** " << endl;
    cout << "===================================================================" << endl;
  }
  
}


void Main_menu() {
  cout << "\n\t. . . . . . . . . . TOP . . . . . . . . . . \n\n";
  int arr[PROBLEM_ROW][PROBLEM_COL];
  
  bool done = false;
  char command;
  
  do {
    display_menu();
    cin >> command;
    
    switch (toupper(command)) {
      case 'P':
        default_puzzle();
        break;
      case 'I':  // insert problem array from user input
        insert_puzzle(arr);
        user_puzzle(arr);
        break;
      case 'Q':  // quit or exit program
      case 'X':
        done = true;
        break;
    }
    
  } while (!done);
  
  cout << "\n . . . . . . . . . . END  . . . . . . . . . . \n\n";
}

#endif // SEARCH_INTERFACE
