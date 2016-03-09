"""
Implementing INK-spline kernel and related function-argument for SVC
See DOCs for more info

Author:     Sergey Ivanychev
Revision:   1
"""

import numpy as np
from scipy.misc import comb

def _is_integer(val):
    return isinstance(val, (int, np.int32, np.int64))

def _sort_xy(x: np.ndarray, y: np.ndarray):
    """
    Gets (n, ) and (n, ) vectors X, Y and swaps i-th components if x[i] < y[i].
    :param x:   (n, ) ndarray
    :param y:   (n, ) ndarray
    :return:    "swapped" X and Y
    """
    matrix = np.vstack((x, y))
    matrix = np.sort(matrix, axis=1)
    y = matrix[0].copy()
    x = matrix[1].copy()
    return x, y

def _K(x: np.ndarray, y: np.ndarray, degree: int, a: int) -> float:
    """
    Implements not yet normalised multidimensional spline

    :param x:          (n, ) ndarray
    :param y:          (n, ) ndarray
    :param degree:     int;  see ink()
    :param a:          int;  see ink()
    :return:           float; unnormalized kernel value
    """
    S = np.zeros(x.shape[0])
    a = np.zeros(x.shape[0]) + a
    x, y = _sort_xy(x, y)
    for r in range(degree + 1):
        S += np.power(x - a, r)*np.power(y - a, r) +\
        1.0/(2 * degree - r + 1) * comb(degree, r)*np.power(x - y, r)*np.power(y - a, 2*degree - r + 1)
    return np.multiply.reduce(S)


def ink(x: np.ndarray, y: np.ndarray, degree: int, a: int = -3) -> float:
    """
    Implements normalised multidimensional spline
    :param x:       (n, ) ndarray
    :param y:       (n, ) ndarray
    :param degree:  int > 0         The degree of the spline being built
    :param a:       the left side of the interval where the knots are located
    :return:        computed kernel value
    """
    assert _is_integer(degree) and degree > 0, "Degree must be positive integer"
    assert isinstance(x, np.ndarray) and isinstance(y, np.ndarray), "X and Y must be numpy arrays"
    assert len(x.shape) == len(y.shape) == 1, "X and Y must have only one dimension"

    return _K(x, y, degree, a) / np.power(_K(x, x, degree, a) * _K(y, y, degree, a), 1/2)

def ink_svc_get(degree: int, a: int = -3):
    """
    SVC-argument custom kernel function generator
    :param degree: see ink()
    :param a: see ink()
    :return: ink_svc() function with custom degree and a parameters built in
    """
    def ink_svc(X:np.ndarray):
        n_samples = X.shape[0]
        kernel_vals = np.zeros((n_samples, n_samples))
        for i in range(n_samples):
            for j in range(i, n_samples):
                kernel_vals[i][j] = kernel_vals[j][i] = ink(X[i], X[j], degree=degree, a=a)
        return kernel_vals

    return ink_svc
