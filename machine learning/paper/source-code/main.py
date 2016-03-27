"""
The major routines implemented here

Author:     Sergey Ivanychev
Revision:   3
"""

import utils
from utils import test_classifier
from utils import test_classifiers
import sys
import ink
import numpy as np



def dataset_size(dataset):
    return dataset[0].shape[0]

def main(argv):
    clfs = utils.get_all_classifiers(spec_verbose=False)
    clf = clfs[4]

    X, y, _ = utils.get_dataset("housing")
    train_idx = list(range(405))
    test_idx = list(range(405, 506))
    X_train, X_test = utils.scale(X, train_idx, test_idx)
    print(np.min(X_train, axis=0))
    clf.fit(X_train, y[train_idx])
    clf.predict(X_test)

    # X, y = test_classifier("housing", clf)
    # print(np.minimum(X, axis=0))
    # K = ink.get_sklearn_ink(degree=1, a=-3)
    # print(K(X, X))
    return 0



if __name__ == "__main__":
    sys.exit(main(sys.argv))
