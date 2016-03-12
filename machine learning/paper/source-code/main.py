"""
The major routines implemented here

Author:     Sergey Ivanychev
Revision:   2
"""

import sys
import german
import heart
import wine
from sklearn.cross_validation import KFold
# import random
import classifiers
from itertools import combinations


def get_data():
    """
    Loads data from processed sources
    :return: list of (X, y) tuples
    """
    data = []
    data.append(german.load())
    data.append(heart.load())
    data.append(wine.load())

    data_dict = {}
    for dataset in data:
        data_dict[dataset[2]] = (dataset[0], dataset[1])
    return data_dict

# def subsets(n):
#     nums = list(range(n))
#     subsets = []
#     for i in range(1, n):
#         subsets += list(combinations(nums, i))
#     return subsets

def get_classifier_specs():
    """
    Procedure specifies interesting kernels that are observed in the project.
    If you want to change the set of classifiers, you are welcome to edit this function.
    Specs format available in docs and classifiers.py module
    :return: list of kernel specs, that are processed in get_classifiers()
    """
    specs = []
    specs.append(["linear"])
    specs.append(["poly", 2])
    specs.append(["poly", 3])
    specs.append(["ink", 1, -3])
    specs.append(["ink", 2, -3])
    for i in [0.0001, 0.001, 0.01, 0.1, 1]:
        specs.append((["rbf", i]))
    return specs


# def classifiers_subset_generator():
#     specs = get_classifier_specs()
#     sets = subsets(len(specs))
#     random.shuffle(sets)
#     for index_set in sets:
#         current_specs = [specs[i] for i in index_set]
#         clfs = classifiers.get(current_specs)
#         yield clfs

def get_margins(clfs, X_train):
    ...

def analyse(dataset, folds):
    specs = get_classifier_specs()
    clfs = classifiers.get(specs)
    scores = [[] for i in range(len(clfs))]
    for train, test in folds:
        X_train, X_test = dataset[0][train], dataset[0][test]
        Y_train, Y_test = dataset[1][train], dataset[1][test]
        for idx, clf in enumerate(clfs):
            clf.fit(X_train, Y_train)
            scores[idx].append(clf.score(X_test, Y_test))
        aggregator_data = get_margins(clfs, X_train)



def dataset_size(dataset):
    return dataset[0].shape[0]

def main(argv):
    databank = get_data()
    for dataset in databank:
        folds = KFold(dataset_size(dataset), n_folds=5, shuffle=True, random_state=42)
        analyse(dataset, folds)




if __name__ == "__main__":
    sys.exit(main(sys.argv))