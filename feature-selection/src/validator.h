#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <math.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "./classifier.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Validator {
 public:
  /**
   * @brief Construct a new Validator object
   */
  Validator();

  /**
   * @brief evaluates the performance of the classifier using a leave-one-out
   *        cross validation scheme
   *
   * @param features the select features to use for the classifier
   * @param classifier the classifier to use for the evaluation
   * @param data the training data set
   * @return float the accuracy of the classifier
   */
  float evaluate(const vector<int>& features, NN& classifier, const vector<vector<float> >& data);

 private:
  /**
   * @brief Calculate the default rate of the classifier using the formula
   *        rate = size of the most common class) / size of dataset
   *
   * @param data the training data set
   * @return float the default rate of the classifier
   */
  float default_rate(const vector<vector<float> >& data);
};

Validator::Validator() {
}

float Validator::evaluate(const vector<int>& features, NN& classifier, const vector<vector<float> >& data) {
  const bool debug = false;
  float number_correctly_classified = 0.0;

  if (features.size() == 0) {  // if there is no feature, use the default rate
    return default_rate(data);
  }

  for (int i = 0; i < data.size(); i++) {
    auto start = chrono::steady_clock::now();

    float label_object_to_classify = data[i][0];  // class label of object_to_classify

    if (debug && i < 5) {
      cout << "\n " << std::string(100, '-') << "\n";

      cout << "Looping over i, at the: " << i << " location" << endl;
      cout << "   object[" << i << "] is in class: " << label_object_to_classify << endl;
    }

    float nearest_neighbor_label = classifier.Test(i, features);
    if (nearest_neighbor_label == label_object_to_classify) {
      number_correctly_classified++;
    }
    auto end = chrono::steady_clock::now();

    if (debug && i < 5) {
      cout << "   Validator:: step cost: "
           << chrono::duration_cast<chrono::microseconds>(end - start).count()
           << " microseconds" << endl;
    }
  }

  return float(number_correctly_classified / data.size());
}

// =============================================================================
// ============================= Private functions =============================
// =============================================================================

float Validator::default_rate(const vector<vector<float> >& data) {
  float count = 0.0;

  for (int i = 0; i < data.size(); i++) {
    if (data[i][0] == 1) {
      count++;
    }
  }
  if (count < data.size() / 2) {
    count = data.size() - count;
  }
  return float(count / data.size());
}

#endif  // VALIDATOR_H
