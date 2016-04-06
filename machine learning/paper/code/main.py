"""
The major routines implemented here

Author:     Sergey Ivanychev
Revision:   3
"""

import utils
from utils import test_classifier
from utils import test_classifiers
from sklearn.preprocessing import StandardScaler
import warnings
import ink
import numpy as np
import sys



def dataset_size(dataset):
    return dataset[0].shape[0]

def main(argv):
    clfs = utils.get_all_classifiers()
    clf = clfs[0]
    X_train, X_test = test_classifier("housing", clf)
    print(X_train)



if __name__ == "__main__":
    sys.exit(main(sys.argv))
