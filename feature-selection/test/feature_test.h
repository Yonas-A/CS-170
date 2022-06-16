#ifndef FEATURE_TEST_H
#define FEATURE_TEST_H

#include <iostream>
#include <chrono>

#include "../src/features.h"

using namespace std;

void feature_test_forward() {
  Features f;
  cout << std::string(80, '-') << endl;
  cout << "Forward Selection: " << endl;
  auto start = chrono::steady_clock::now();

  //  f.forward_selection(10, false);
  f.forward_selection(40, true);

  auto end = chrono::steady_clock::now();

  cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
  cout << std::string(80, '-') << string(2, '\n');
  
}

void feature_test_backward() {
  Features f;

  cout << std::string(80, '-') << endl;
  cout << "Backward Selection: " << endl;
  auto start = chrono::steady_clock::now();
  
//  f.backward_selection(10, false);
  f.backward_selection(40, true);

  auto end = chrono::steady_clock::now();

  cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
  cout << std::string(80, '-') << string(2, '\n');
}
#endif  // FEATURE_TEST_H
