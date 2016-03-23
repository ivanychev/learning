"""
Module imports sample-feature matrix of housing, UCI

Type:       classification
Author:     Sergey Ivanychev
Revision:   1
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import normalize

def load(path: str ="../data/housing") \
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
    return normalize(X), Y, "housing"