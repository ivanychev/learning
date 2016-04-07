# The source code

## Source files description

- `stuff.ipynb` – Jupyter Notebook containing the experiment
- `testing_classifiers.ipynb` – testing every model ROC
- `supermodel.ipynb` – supermodel class implementation and testing
- `heart.py`, `german.py`, `housing.py`, `spam.py`, `wine.py` – data processing modules
- `metric.py` – kernel distance implementation
- `ink.py` – INK-spline SVM kernel implementation (not available on the `scikit-learn`)
- `classifiers.py` – loading list of kernels (implemented as dictionaries to unpack using `SVC` from `scikit-learn`)
- `utils.py` – utilities for loading data and classifiers

## The process

The process is divided into several parts

1. Reading the data
    - Processing downloaded files
    - Storing them in `pandas.DataFrame`
    - Getting "sample-feature" matrix
2. Implementing the set of classifying SVMs with different kernels
3. Implementing class for supermodel
4. Do these better


### Adult

[Link](https://archive.ics.uci.edu/ml/datasets/Adult)

### Heart-disease

[Link](https://archive.ics.uci.edu/ml/datasets/Heart+Disease)

### Housing

[Link](https://archive.ics.uci.edu/ml/datasets/Housing)

### Spambase

[Link](https://archive.ics.uci.edu/ml/datasets/Spambase)

### Statlog-german

[Link](https://archive.ics.uci.edu/ml/datasets/Statlog+(German+Credit+Data))

### Wine

[Link](https://archive.ics.uci.edu/ml/datasets/Wine)

### Yeast

[Link](https://archive.ics.uci.edu/ml/datasets/Yeast)
