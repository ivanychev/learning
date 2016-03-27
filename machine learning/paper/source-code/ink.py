"""
Implementing INK-spline kernel and related function-argument for SVC
See DOCs for more info

Author:     Sergey Ivanychev
Revision:   3
"""

from functools import partial
import numpy as np
from scipy.misc import comb

glob = 0

def _is_integer(val):
    return isinstance(val, (int, np.int32, np.int64))

def K(X: np.ndarray, Y: np.ndarray, degree: int, a: int) -> np.ndarray:
    gram = np.zeros((X.shape[0], Y.shape[0]))
    verbose_len = X.shape[0]
    for idx, x in enumerate(X):
        S = np.zeros(Y.shape)
        for r in range(degree + 1):
            S += ((x - a)*(Y - a))**r +\
            1.0/(2 * degree - r + 1) * comb(degree, r)*((np.abs(x - Y))**r)*(np.minimum(x, Y) - a)**(2*degree - r + 1)
        gram_row = np.multiply.reduce(S, axis=1)
        gram[idx] = gram_row
        if idx % 500 == 0:
            percentile = idx / verbose_len * 100
            print("%f %% ready" % percentile)
    return gram

def K_norm(X: np.ndarray, degree: int, a: int, axis: str) -> np.ndarray:
    assert axis == "x" or axis =="y", "Invalid axis argument"
    gram = np.zeros((X.shape[0], X.shape[0]))
    for idx, x in enumerate(X):
        S = np.zeros(x.shape)
        for r in range(degree + 1):
            S += ((x - a)*(x - a))**r +\
            1.0/(2 * degree - r + 1) * comb(degree, r)*(0**r)*(x - a)**(2*degree - r + 1)
        S = np.multiply.reduce(S)
        gram[idx] = S
    if axis == "x":
        return gram
    if axis == "y":
        return np.transpose(gram)


def ink(x: np.ndarray, y: np.ndarray, degree: int, a: int = -3) -> np.ndarray:
    assert _is_integer(degree) and degree > 0, "Degree must be positive integer"
    assert isinstance(x, np.ndarray) and isinstance(y, np.ndarray), "X and Y must be numpy arrays"

    if len(x.shape) == 1:
        x = x.reshape(1, x.shape[0])
    if len(y.shape) == 1:
        y = y.reshape(1, y.shape[0])
    return K(x, y, degree, a) / np.sqrt(K_norm(x, degree, a, "x") * K_norm(y, degree, a, "y"))

def get_sklearn_ink(degree: int, a: int):
    return partial(K, degree=degree, a=a)