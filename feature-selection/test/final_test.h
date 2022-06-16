#ifndef FINAL_TEST_H
#define FINAL_TEST_H

#include "../src/classifier.h"
#include "../src/validator.h"
#include "../src/features.h"

using namespace std;

void small_table_test() {
  NN c;
  vector<vector<float> > t = c.getData();

  Validator v;
  vector<int> features = {1,2,3,4,5,6,7,8,9,10};
  float accuracy = v.evaluate(features, c, t);

  cout << endl
       << "using features: {";
  for (auto x : features)
    cout << x << " ";
  cout << "} on the small-test-dataset we got an accuracy of: " << accuracy << endl;
}

void big_table_test() {
  NN c(true);
  vector<vector<float> > t = c.getData();

  Validator v;
  vector<int> features;
  for (int i = 0; i < 40; i++){
    features.push_back(i);
  }
  float accuracy = v.evaluate(features, c, t);

  cout << endl
       << "using features: {";
  for (auto x : features)
    cout << x << " ";
  cout << "} on the Large-test-dataset we got an accuracy of: " << accuracy << endl;
}

#endif  // FINAL_TEST_H
