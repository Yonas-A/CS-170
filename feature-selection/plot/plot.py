import matplotlib.pyplot as plt
import pandas as pd
from sklearn import datasets, neighbors
from mlxtend.plotting import plot_decision_regions

def test_Large():
  data = pd.read_csv('../dataset/large.csv')
  k = 1
  x = data[['feature23','feature27']].values
  y = data['class'].astype(int).values

  clf = neighbors.KNeighborsClassifier(n_neighbors=k)
  clf.fit(x, y)
  plot_decision_regions(x, y, clf=clf, legend=2)
  plt.xlabel('feature23')
  plt.ylabel('feature27')
  plt.title('Large dataset')
  plt.show()

def test_Small():
  data = pd.read_csv('../dataset/small.csv')
  k = 1
  x = data[['feature8','feature10']].values
  y = data['class'].astype(int).values

  clf = neighbors.KNeighborsClassifier(n_neighbors=k)
  clf.fit(x, y)
  plot_decision_regions(x, y, clf=clf, legend=2)
  plt.xlabel('feature8')
  plt.ylabel('feature10')
  plt.title('Small dataset')
  plt.show()

test_Small()
test_Large()