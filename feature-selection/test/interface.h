#ifndef FEATURE_SELECTION_INTERFACE_H
#define FEATURE_SELECTION_INTERFACE_H

#include <stdlib.h>

#include <chrono>
#include <iostream>

#include "../src/features.h"

using namespace std;

const std::string DATASET[] = {"small", "large"};

void display_menu() {
  cout << "[1] Forward SELECTION     [2] BACKWARD SELECTION   [3] Quit:    ";
}

void display_dataset_Choice() {
  cout << "[1] SMALL dataset     [2] LARGE dataset     [3] Quit :  ";
}

void forward_selection_test() {
  display_dataset_Choice();
  int fileChoice;
  cin >> fileChoice;
  if (fileChoice != 1 && fileChoice != 2)
    exit(1);
  bool large = fileChoice == 2;
  int total = large ? 40 : 10;

  Features f;
  cout << "===================================================================\n " << endl;

  cout << "Forward Selection on " << DATASET[fileChoice-1] << " dataset with: " << total
       << " features" << endl;

  auto start = chrono::steady_clock::now();

  vector<int> set = f.forward_selection(total, large);

  auto end = chrono::steady_clock::now();
  auto final = float(chrono::duration_cast<chrono::milliseconds>(end - start).count())/float(1000);
  cout << "time spent: " << final << " seconds\n";
  cout << "===================================================================\n " << endl;
}

void backward_selection_test() {
  display_dataset_Choice();

  int fileChoice;
  cin >> fileChoice;
  if (fileChoice != 1 && fileChoice != 2)
    exit(1);
  bool large = fileChoice == 2;
  int total = large ? 40 : 10;

  Features f;
  cout << "===================================================================\n " << endl;

  cout << "Backward Selection on " << DATASET[fileChoice-1] << " dataset with: " << total
       << " features" << endl;

  auto start = chrono::steady_clock::now();

  vector<int> set = f.backward_selection(total, large);

  auto end = chrono::steady_clock::now();

  auto final = float(chrono::duration_cast<chrono::milliseconds>(end - start).count())/float(1000);
  cout << "time spent: " << final << " seconds\n";
  cout << "===================================================================\n " << endl;
}

void Main_menu() {
  cout << "\n\t. . . . . . . . . . TOP . . . . . . . . . . \n\n";

  bool done = false;
  int command;

  do {
    display_menu();
    cin >> command;

    switch (command) {
      case 1:
        forward_selection_test();
        break;
      case 2:
        backward_selection_test();
        break;
      default:
        done = true;
        break;
    }

  } while (!done);

  cout << "\n . . . . . . . . . . END  . . . . . . . . . . \n\n";
}

#endif  // FEATURE_SELECTION_INTERFACE_H
