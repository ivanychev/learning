"""
The major routines implemented here

Author:     Sergey Ivanychev
Revision:   1
"""

import sys
import german
import heart
import wine
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
    return data

def subsets(n):
    nums = list(range(n))
    subsets = []
    for i in range(1, n):
        subsets += list(combinations(nums, i))
    return subsets

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

def classifiers_subset():
    specs = get_classifier_specs()
    sets = subsets(len(specs))
#    random.shuffle(sets)
    for index_set in sets:
        current_specs = [specs[i] for i in index_set]
        clfs = classifiers.get(current_specs)
        yield clfs

def get_margins(data, clfs):
    ...

def main(argv):
    data = get_data()
    for clfs in classifiers_subset():
        ...



if __name__ == "__main__":
    sys.exit(main(sys.argv))