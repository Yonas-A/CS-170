#ifndef VALIDATOR_TEST_H
#define VALIDATOR_TEST_H

#include <iostream>

#include "../src/classifier.h"
#include "../src/validator.h"

void validator_on_small() {
  NN c;
  vector<vector<float> > t = c.getData();

  Validator v;
  vector<int> features = {4, 5, 7, 10};
  float accuracy = v.evaluate(features, c, t);

  cout << "\nusing features: {";
  for (auto x : features)
    cout << x << " ";
  cout << "} on the small-test-dataset we got an accuracy of: " << accuracy << endl;
}

void validator_on_large() {
  NN c(true);
  vector<vector<float> > t = c.getData();

  Validator v;
  vector<int> features = {4, 5, 7, 10};
  float accuracy = v.evaluate(features, c, t);

  cout << "\nusing features: {";
  for (auto x : features)
    cout << x << " ";
  cout << "} on the large-test-dataset we got an accuracy of: " << accuracy << endl;
}

#endif  // VALIDATOR_TEST_H
