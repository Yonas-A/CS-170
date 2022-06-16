#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <math.h>

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

using namespace std;

const string SMALL_PERSONAL_DATASET = "../dataset/CS170_Spring_2022_Small_data__110.txt";
const string LARGE_PERSONAL_DATASET = "../dataset/CS170_Spring_2022_Large_data__110.txt";

const string SMALL_TEST_DATASET = "../dataset/Small-test-dataset.txt";
const string LARGE_TEST_DATASET = "../dataset/Large-test-dataset.txt";

/**
 * @brief A Nearest Neighbor classifier class that uses the euclidean distance
 * to determine the closest point in the training data set.
 */
class NN {
 public:
  /**
   * @brief Construct a new NN object
   */
  NN(bool bigFile = false);

  /**
   * @brief Construct a new NN object from the \p other NN object
   *
   * @param other the other NN object to copy from
   */
  NN(const NN& other);

  /**
   * @brief assignment operator to assign \p RHS to the current NN object
   *
   * @param RHS the other NN object to copy from
   * @return the current NN object that is a duplicate of RHS
   */
  NN& operator=(const NN& RHS);

  /**
   * @brief destructor to delete the current NN object
   */
  ~NN();

  /**
   * @brief get the data object
   *
   * @return vector<vector<float> > the data object
   */
  vector<vector<float> > getData();

  /**
   * @brief train the classifier model using the given instance \p ids
   *
   * @param ids the set of training instances or ID
   */
  void Train(const vector<int>& ids);

  /**
   * @brief predict the class label for the given instance \p id based on the
   * given \p features
   *
   * @param id the instance ID to classify ( from the dataset)
   * @param features the select features to use for the classifier
   * @return the class label of the given instance ID as an integer
   */
  int Test(const int& id, const vector<int>& features);

  /**
   * @brief prints the dataset and the normalized dataset
   *
   * @param outs ostream operator to print to
   * @param nn the NN object to print
   * @return std::ostream& the ostream operator
   */
  friend std::ostream& operator<<(ostream& outs, const NN& nn);

 private:
  /**
   * @brief _file is the file stream that is used to read the file
   *
   */
  std::ifstream _file;

  /**
   * @brief _data  the vector that holds the dataset from the file. For
   * convenient it is normalized using the \code x = x - mean /stDev
   */
  std::vector<std::vector<float> > _data;

  /**
   * @brief opens the file given by \p fName
   *
   * @param fName the file name
   * @return true if the file was opened successfully otherwise false
   */
  bool openFile(const std::string& fName);

  /**
   * @brief read the file and store the data in the data vector
   */
  void readFile();

  /**
   * @brief normalize the dataset using the formula x = x - mean(x) / std(x)
   */
  void normalize();
};

// =============================================================================
//                        function implementations (Public)
// =============================================================================

NN::NN(bool bigFile) {
  if (bigFile) {
    openFile(LARGE_PERSONAL_DATASET);
  } else {
    openFile(SMALL_PERSONAL_DATASET);
  }
  readFile();
  normalize();
}

NN::NN(const NN& other) {
  copy(other._data.begin(), other._data.end(), back_inserter(_data));
}

NN& NN::operator=(const NN& RHS) {
  if (this != &RHS) {  // self-assignment check
    copy(RHS._data.begin(), RHS._data.end(), back_inserter(_data));
  }
  return *this;
}

NN::~NN() {
}

vector<vector<float> > NN::getData() {
  vector<vector<float> > temp;
  copy(_data.begin(), _data.end(), back_inserter(temp));
  return temp;
}

void NN::Train(const vector<int>& ids) {
}

int NN::Test(const int& id, const vector<int>& features) {
  const bool debug = false;
  std::vector<float> object_to_classify(_data[id].begin(), _data[id].end());
  float nearest_neighbor_distance = INFINITY;
  float nearest_neighbor_location = INFINITY;
  float nearest_neighbor_label = -INFINITY;

  for (int i = 0; i < _data.size(); i++) {
    if (i != id) {
      if (debug && id < 5)
        cout << "   Ask if " << id << " is  nearest neighbor with: " << i << endl;
      std::vector<float> temp;

      for (int j = 0; j < features.size(); j++) {
        int a = features[j];
        temp.push_back(pow(object_to_classify[a] - _data[i][a], 2));
      }

      float sum = 0.0;
      std::for_each(temp.begin(), temp.end(), [&](float n) {
        sum += n;
      });

      float distance = sqrt(sum);
      if (distance <= nearest_neighbor_distance) {
        nearest_neighbor_distance = distance;
        nearest_neighbor_location = i;
        nearest_neighbor_label = _data[nearest_neighbor_location][0];
      }
    }
  }
  if (debug && id < 5)
    cout << "Its nearest neighbor is " << nearest_neighbor_location
         << " which is in class " << nearest_neighbor_label << endl;

  return nearest_neighbor_label;
}

std::ostream& operator<<(ostream& outs, const NN& nn) {
  for (int i = 0; i < nn._data.size(); i++) {
    for (int j = 0; j < nn._data[i].size(); j++) {
      outs << std::setw(16) << std::scientific << nn._data[i][j] << " ";
    }
    outs << std::endl;
  }

  return outs;
}

// =============================================================================
// ===================== Private functions' implementation =====================
// =============================================================================

bool NN::openFile(const std::string& fName) {
  _file.open(fName);
  if (_file.fail()) {
    std::cout << "file did not open!" << std::endl;
    return -2;
  }
  return true;
}

void NN::readFile() {
  std::string line;

  while (std::getline(_file, line)) {
    std::vector<float> row;

    std::stringstream ss(line);
    float value;
    while (ss >> value) {
      row.push_back(value);
    }
    _data.push_back(row);
  }
  _file.close();
}

void NN::normalize() {
  vector<vector<float> > temp;
  copy(_data.begin(), _data.end(), back_inserter(temp));

  for (int feature = 1; feature < temp[0].size(); feature++) {
    std::vector<float> col;

    for (int i = 0; i < temp.size(); i++) {
      col.push_back(temp[i][feature]);
    }

    float sum = std::accumulate(std::begin(col), std::end(col), 0.0);
    float mean = sum / col.size();
    float accumulator = 0.0;
    std::for_each(std::begin(col), std::end(col), [&](const float d) {
      accumulator += (d - mean) * (d - mean);
    });

    float stdDev = sqrt(accumulator / (col.size() - 1));
    for (int i = 0; i < col.size(); i++) {
      float normalized = (col[i] - mean) / stdDev;
      temp[i][feature] = normalized;
    }
  }
  _data = temp;
}

#endif  // CLASSIFIER_H
