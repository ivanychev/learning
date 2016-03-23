"""
Module imports sample-feature matrix of spambase, UCI

Type:       classification
Author:     Sergey Ivanychev
Revision:   1
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import normalize

def load(path: str ="../data/spambase") \
-> (np.ndarray, np.ndarray):
    """
    :param path:    relative path to the folder that contains files such as
                        - spambase.data
    :return:        X   (samples x n_features)  numpy.ndarray
                    Y   (samples, )             numpy.ndarray
    """
    names = [str(i + 1) for i in range(58)]
    df = pd.read_csv(path + "/spambase.data",
                     sep=",", index_col=False, engine='python', names=names)
    target = "58"
    features_names = names[:]
    features_names.remove(target)

    X = df[features_names].as_matrix()
    Y = df[target].as_matrix()
    return normalize(X), Y, "spambase"
