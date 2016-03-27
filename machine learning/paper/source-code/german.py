"""
Module imports sample-feature matrix of German Credits data set from UCI

Type:       classification
Author:     Sergey Ivanychev
Revision:   2
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import scale

def load(path: str ="../data/statlog-german", raw=False) \
-> (np.ndarray, np.ndarray):
    """
    :param path:    relative path to the folder that contains files such as
                        - german.data-numeric
    :return:        X   (samples x n_features)  numpy.ndarray
                    Y   (samples, )             numpy.ndarray
    """
    names = [str(i + 1) for i in range(25)]
    df = pd.read_csv(path + "/german.data-numeric",
                     sep="[ ]+", index_col=False, engine='python', names=names)
    target = "25"
    features_names = names[:]
    features_names.remove(target)

    X = df[features_names].as_matrix()
    Y = df[target].as_matrix()
    if raw==False:
        X = scale(X)
    return np.asfarray(X), Y, "german"
