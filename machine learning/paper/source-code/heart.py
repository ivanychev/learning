"""
Module imports sample-feature matrix of Heart Decease data set from UCI.
This module uses only data collected in Cleveland, so the file
"preceeded.cleveland.data" is required

Type:       classification, regression
Author:     Sergey Ivanychev
Revision:   2
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import scale


def load(path: str ="../data/heart-disease", mode: str = "classification", 
    raw=False) \
-> (np.ndarray, np.ndarray):
    """
    :param path:    string
                    relative path to the folder that contains files such as
                        - preceeded.cleveland.data
    :param mode     string in ["classification", "regression"]
                    specializes the returned answers array
    :return:        X   (samples, n_features)   numpy.ndarray
                    Y   (samples, )             numpy.ndarray
    :note:          file contains 6 NA values so the objects they lay in are
                    suppressed
    """
    assert mode in ["classification", "regression"]

    names = [str(i + 1) for i in range(14)]
    df = pd.read_csv(path + "/processed.cleveland.data", header=None, names=names)
    df = df[(df["12"] != "?") & (df["13"] != "?")]
    for col in ["12", "13"]:
        df[col] = pd.to_numeric(df[col])
    target = "14"
    if mode == "classification":
        df[target] = df[target].apply(lambda x: 1 if x > 0 else 0)
    features = names
    features.remove(target)
    X = df[features].as_matrix()
    Y = df[target].as_matrix()
    if raw==False:
        X = scale(X)
    return np.asfarray(X), Y, "heart"
