# CS170-Nearest-Neighbor-Classifier

## About the Code

This is a project that uses `feature selection` to find the best set of features
for a `Nearest Neighbor classifier` algorithm.

## Design

### Classifier class

This class creates a `Nearest Neighbor Classifier` model that uses the euclidean
distance to determine the closest neighbors to a point in the training data set.

### Features class

This class creates a `feature selection` algorithm that will select the best
subset of features for a dataset that produce the highest accuracy for a given
set of features. `Backward selection` and `Forward selection` are used only
select set of features that result in the best accuracy. Both the `backward` and
`forward` selection algorithm implement a greedy hill-climbing search where the
optimum solution is picked at every iteration. In addition the selection
algorithms terminate when the current accuracy of the set drop below that of the
previous set.

### Validator class

This class evaluates the performance of the `Nearest Neighbor Classifier` using
a `leave-one-out cross validation` scheme.

### plots

The `plot.py` scripts provides a way to plot a Nearest classifier model with two
features from the dataset for a better understanding of the feature selection
results.

### Raw Data

The raw data are contained in a text file with the horizontal rows representing
a single data point. The first column of each row represent the class id of the
data point while the rest rest of the column represent the different features
and their data for that single data point. The small dataset files contain 10
features and 100 data points while the large dataset files contain 40 features
and over 1000 data points.

## Configuration

### C++

a `C++ 11` enabled compiler

### Py

To run the program, first you need do download python packages. From within the
directory open the terminal and run the command

```bash
pip install -r requirements.txt
```

to install all the dependencies used for this program. To avoid installing
python packages globally which could break system tools or other projects a
python virtual environment is recommended. After that run the command

```bash
python3 plot.py
```

to plot the data. If all succeeds then a python plot should appear with the
features.

## Results

Both `backward` and `forward` feature selections algorithms have good merit on
improving accuracy of the classification model. In terms of speed forward
selection has a significant lead over backward selection as it starts with no
features and only observe small sets at a time while we consider the entire set
of features for backward selection. If the best set of features are located at
the start then forward selection does really well while backward selection will
go thru a number of features to visit the same features.
