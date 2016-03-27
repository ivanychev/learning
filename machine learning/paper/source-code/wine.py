"""
Module imports sample-feature matrix of Wine Quality data set from UCI.
This module uses only data about white wine.

Type:       classification, regression
Author:     Sergey Ivanychev
Revision:   1
"""

import numpy as np
import pandas as pd
from sklearn.preprocessing import scale

def load(path: str ="../data/wine", mode: str = "classification", raw=False) \
-> (np.ndarray, np.ndarray):
    df = pd.read_csv(path + "/winequality-white.csv", sep=";")
    cols = list(df.columns.values)
    target = "quality"
    cols.remove(target)
    X = df[cols].as_matrix()
    Y = df[target].as_matrix()
    if mode == "classification":
        Y = np.int32(Y >= 6)
    if raw==False:
        X = scale(X)
    return np.asfarray(X), Y, "wine"
