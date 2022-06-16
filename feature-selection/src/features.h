#ifndef FEATURES_H
#define FEATURES_H

#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "./classifier.h"
#include "./validator.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;

ostream& operator<<(ostream& os, const vector<int>& v) {
  std::string str;
  for (int i = 0; i < v.size(); i++) {
    str = (i < v.size() - 1) ? ", " : "";
    os << v[i] << str;
  }
  return os;
}
/**
 *
 * @brief A feature selection class to select the set of features that produce .
 *       the highest accuracy for a given set of features.
 */
class Features {
 public:
  /**
   * @brief Constructor for the Features class.
   *
   */
  Features();

  /**
   * @brief Destructor for the Features class.
   *
   */
  ~Features();

  /**
   * @brief find the best features to use for classification using forward
   *       selection algorithm.
   *
   * @param total the total number of features available
   * @param bigFile the file type ( only for this assignment)
   * @return vector<int> the set of features with the highest accuracy
   */
  vector<int> forward_selection(const int& total, bool bigFile = false);

  /**
   * @brief find the best features to use for classification using backward
   *       selection algorithm.
   *
   * @param total the total number of features available
   * @param bigFile the file type ( only for this assignment)
   * @return vector<int> the set of features with the highest accuracy
   * \note need to specify the total size beforehand since different datasets have different feature counts
   */
  vector<int> backward_selection(const int& total, bool bigFile = false);

 private:
  /**
   * @brief generates a random number between 0 and 100
   *
   * @return double the generated number
   */
  float random_gen();
};

Features::Features() {
}

Features::~Features() {
}

vector<int> Features::forward_selection(const int& total, bool bigFile) {
  NN classifier(bigFile);
  Validator v;
  vector<vector<float> > data = classifier.getData();

  pair<vector<int>, float> subset = {vector<int>(), 0};        // the final set of features
  subset.second = v.evaluate(subset.first, classifier, data);  // set to default rate

  cout << "\n------------------------------------" << endl;
  cout << "{ " << subset.first << " } | " << subset.second << "%" << endl;
  cout << "------------------------------------" << endl;

  for (int i = 1; i < total + 1; i++) {
    cout << "On the " << i << "-th level of the search tree: " << endl;
    int feature_to_add = -1;
    float best_accuracy = 0;
    vector<int> current = subset.first;  // current set of features

    for (int j = 1; j < total + 1; j++) {
      if (find(current.begin(), current.end(), j) == current.end()) {
        current.push_back(j);

        float accuracy = v.evaluate(current, classifier, data);

        cout << "   -- Using feature(s) {" << current << "} accuracy is " << accuracy
             << "%" << endl;

        if (accuracy > best_accuracy) {
          best_accuracy = accuracy;
          feature_to_add = j;
        }
        current.pop_back();  // remove the last element
      }
    }
    if (subset.second > best_accuracy) {
      cout << "   accuracy has decreased. Exiting\n"
           << endl;
      break;
    } else {
      subset.first.push_back(feature_to_add);
      subset.second = best_accuracy;
      cout << "   on level " << i << ", feature " << feature_to_add
           << " added to set {" << current << "} with an accuracy of "
           << best_accuracy << "%" << endl
           << endl;
    }
  }

  cout << "\n------------------------------------" << endl;
  cout << "best feature(s) { " << subset.first << " } -> " << subset.second << "%" << endl;

  return subset.first;
}

vector<int> Features::backward_selection(const int& total, bool bigFile) {
  NN classifier(bigFile);
  Validator v;
  vector<vector<float> > data = classifier.getData();

  pair<vector<int>, float> subset = {vector<int>(), 0.0};

  for (int i = 1; i < total + 1; i++) {
    subset.first.push_back(i);
  }
  subset.second = v.evaluate(subset.first, classifier, data);  // set to default rate

  cout << "{ " << subset.first << " } | " << subset.second << "%" << endl
       << endl;

  for (int i = 1; i < total + 1; i++) {
    cout << "On the " << i << "-th level of the search tree: " << endl;

    vector<int> current = subset.first;
    float best_accuracy = subset.second;

    int feature_to_remove = -1;
    int current_removed = current.back();
    current.pop_back();

    for (int j = current.size(); j >= 0; j--) {
      float accuracy = v.evaluate(current, classifier, data);

      cout << "   ---- removing feature " << current_removed << " -> accuracy: "
           << accuracy << "%" << endl;

      if (accuracy > best_accuracy) {
        best_accuracy = accuracy;
        subset.first = current;
        subset.second = best_accuracy;
        feature_to_remove = current_removed;
      }
      if(j > 0 ){
      int temp = current_removed;
      current_removed = current[j - 1];
      current[j - 1] = temp;
      }
    }

    if (feature_to_remove > 0) {
      cout << "   on level " << i << " feature " << feature_to_remove
           << " removed. set {" << subset.first << "} -> " << best_accuracy << "%\n"
           << endl;
    } else {
      cout << "   accuracy has decreased. Exiting\n"
           << endl;
      break;
    }
  }

  cout << "\n------------------------------------" << endl;
  cout << "best feature(s) { " << subset.first << " } -> " << subset.second << "%" << endl;

  return subset.first;
}

// =============================================================================
// ============================= private functions =============================
// =============================================================================

float Features::random_gen() {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<> dis(0.0, 100.0);
  return dis(gen);
}

#endif  // FEATURES_H
