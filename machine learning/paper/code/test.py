
# coding: utf-8

# In[3]:

import numpy as np
import numbers
from scipy.misc import comb
import ink

def _is_integer(val):
    return isinstance(val, (int, np.int32, np.int64))


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
            S += ((x - a)*(Y - a))**r +            1.0/(2 * degree - r + 1) * comb(degree, r)*((np.abs(x - Y))**r)*(np.minimum(x, Y) - a)**(2*degree - r + 1)
        gram_row = np.multiply.reduce(S, axis=1)
        gram[idx] = gram_row
    return gram

def K_norm(X: np.ndarray, Y:np.ndarray, degree: int, a: int, axis: str) -> np.ndarray:
    assert axis == "x" or axis =="y", "Invalid axis argument"
    gram = np.zeros((X.shape[0], Y.shape[0]))
    if axis=="x":
        for idx, x in enumerate(X):
            S = np.zeros(x.shape)
            for r in range(degree + 1):
                S += ((x - a)*(x - a))**r +                1.0/(2 * degree - r + 1) * comb(degree, r)*(0**r)*(x - a)**(2*degree - r + 1)
            S = np.multiply.reduce(S)
            gram[idx] = S
    elif axis=="y":
        for idx, y in enumerate(Y):
            S = np.zeros(y.shape)
            for r in range(degree + 1):
                S += ((y - a) * (y - a)) ** r +                      1.0 / (2 * degree - r + 1) * comb(degree, r) * (0 ** r) * (y - a) ** (2 * degree - r + 1)
            S = np.multiply.reduce(S)
            gram[:, idx:idx+1] = S
    else:
        raise ValueError("Invalid axis name")
    return gram


def ink(x: np.ndarray, y: np.ndarray, degree: int, a: int = -3) -> np.ndarray:
    assert _is_integer(degree) and degree > 0, "Degree must be positive integer"
    assert isinstance(x, np.ndarray) and isinstance(y, np.ndarray), "X and Y must be numpy arrays"
    if len(x.shape) == 1:
        x = x.reshape(1, x.shape[0])
    if len(y.shape) == 1:
        y = y.reshape(1, y.shape[0])
    x[x < a] = a
    y[y < a] = a
    return K(x, y, degree, a) / np.sqrt(K_norm(x, y, degree, a, "x") * K_norm(x, y, degree, a, "y"))

def get_sklearn_ink(degree: int, a: int):
    return partial(ink, degree=degree, a=a)


# ## New version

# In[78]:
def make_fat_xy(X, Y):
    fatX = np.tile(X, (Y.shape[0], 1))
    fatY = np.tile(Y, (1, X.shape[0])).reshape(X.shape[0] * Y.shape[0], X.shape[1])
    return fatX, fatY

def f1(fatX, fatY, a):
    return ((fatX - a)*(fatY - a))
def f2(fatX, fatY):
    return (np.abs(fatX - fatY))
def f3(fatX, fatY, a):
    return np.minimum(fatX, fatY) - a

def new_K(X: np.ndarray, Y: np.ndarray, degree: int, a: int) -> np.ndarray:
    fatX, fatY = make_fat_xy(X, Y)

    first = f1(fatX, fatY, a)
    absXYdiff = f2(fatX, fatY)
    XYmin_minus_A = f3(fatX, fatY, a)

    S = np.zeros(fatX.shape)
    for r in range(degree + 1):
        S += first**r +\
            1.0/(2 * degree - r + 1) * comb(degree, r)*(absXYdiff**r)*(XYmin_minus_A)**(2*degree - r + 1)
    S = np.multiply.reduce(S, axis=1)
    gram = np.transpose(S.reshape((Y.shape[0], X.shape[0])))
    return gram

def new_K_norm(X: np.ndarray, Y: np.ndarray, degree: int, a: int) -> np.ndarray:
    Sx = np.zeros(X.shape)
    Sy = np.zeros(Y.shape)
    firstX = ((X - a)*(X - a))
    firstY = ((Y - a)*(Y - a))
    for r in range(degree + 1):
        Sx += firstX**r + 1.0/(2 * degree - r + 1) * comb(degree, r)*(0**r)*(X - a)**(2*degree - r + 1)
        Sy += firstY**r + 1.0/(2 * degree - r + 1) * comb(degree, r)*(0**r)*(Y - a)**(2*degree - r + 1)
    Sx = np.multiply.reduce(Sx, axis=1)
    Sy = np.multiply.reduce(Sy, axis=1)
    Sx_matrixed = np.tile(Sx.reshape(Sx.shape[0], 1), Sy.shape[0])
    Sy_matrixed = np.tile(Sy, (Sx.shape[0], 1))
    return np.sqrt(Sx_matrixed * Sy_matrixed)



def new_ink(X: np.ndarray, Y: np.ndarray, degree: int, a: int = -3) -> np.ndarray:
    assert _is_integer(degree) and degree > 0, "Degree must be positive integer"
    assert isinstance(X, np.ndarray) and isinstance(Y, np.ndarray), "X and Y must be numpy arrays"
    if len(X.shape) == 1:
        X = X.reshape(1, X.shape[0])
    if len(Y.shape) == 1:
        Y = Y.reshape(1, Y.shape[0])
    X[X < a] = a
    Y[Y < a] = a
    return new_K(X, Y, degree, a) / new_K_norm(X, Y, degree, a)
# In[81]:

X = np.random.random((1000, 50))
Y = np.random.random((1600, 50))

ink(X, Y, 1)
new_ink(X, Y, 1)


