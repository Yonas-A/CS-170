#ifndef CONST_H
#define CONST_H

#include "../src/problem.h"

int impossible[PROBLEM_ROW][PROBLEM_COL] = {
  {1, 2, 3},
  {4, 5, 6},
  {8, 7, 0}};

int puzzle[PROBLEM_ROW][PROBLEM_COL] = {
  {1, 0, 3},
  {4, 5, 6},
  {7, 8, 2}};

int puzzle2[PROBLEM_ROW][PROBLEM_COL] = {
  {5, 0, 3},
  {4, 1, 6},
  {7, 8, 2}};

int puzzle3[PROBLEM_ROW][PROBLEM_COL] = {
  {5, 0, 2},
  {4, 1, 6},
  {3, 8, 7}};

int puzzle4[PROBLEM_ROW][PROBLEM_COL] = {
  {1, 2, 3},
  {5, 7, 4},
  {0, 8, 6}};


int doable[PROBLEM_ROW][PROBLEM_COL] = {
  {0, 1, 2},
  {4, 5, 3},
  {7, 8, 6}};

int hardPuzzle[PROBLEM_ROW][PROBLEM_COL] = {
  {8, 7, 1},
  {6, 0, 2},
  {5, 4, 3}};

Move moves[] = {Move::UP, Move::DOWN, Move::LEFT, Move::RIGHT};

#endif // CONST_H
