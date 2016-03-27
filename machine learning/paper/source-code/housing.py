"""
Module imports sample-feature matrix of housing, UCI

Type:       classification
Author:     Sergey Ivanychev
Revision:   2
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import scale

def load(path: str ="../data/housing", raw=False) \
-> (np.ndarray, np.ndarray):
    """
    :param path:    relative path to the folder that contains files such as
                        - housing.data
    :return:        X   (samples x n_features)  numpy.ndarray
                    Y   (samples, )             numpy.ndarray
    """
    names = [str(i + 1) for i in range(14)]
    df = pd.read_csv(path + "/housing.data",
                     sep="[ ]+", index_col=False, engine='python', names=names)
    df["14"] = df["14"].apply(lambda x: 1 if x > 25 else 0)
    target = "14"
    features_names = names[:]
    features_names.remove(target)

    X = df[features_names].as_matrix()
    Y = df[target].as_matrix()
    if raw==False:
        X = scale(X)
    return np.asfarray(X), Y, "housing"
