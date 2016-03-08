"""
This module loads a set of models used in classification. Supported kernels are
 - Linear
 - RBF
 - INK-spline
 - Polynomial
"""


import numpy as np
import scipy as sc
from sklearn.svm import SVC
import numbers

KERINVAL = "Invalid specification of kernel"

def _is_number(val):
    return isinstance(val, numbers.Number)

def _linear_args(spec):
    assert len(spec) == 1, KERINVAL
    return {"kernel":"linear"}

def _rbf_args(spec):
    assert len(spec) == 2 and _is_number(spec[1]), KERINVAL
    return {"kernel":"rbf", "gamma":float(spec[1])}

def _poly_args(spec):
    assert len(spec) == 2 and _is_number(spec[1]), KERINVAL
    return {"kernel":"poly", "degree":int(spec[1])}

def _ink_args(spec):
    ...

KERNELS = {
    "linear":_linear_args,
    "rbf":_rbf_args,
    "ink":_ink_args,
    "poly":_poly_args
}

def _get_kernel(spec):
    return KERNELS[spec[0]](spec)


def get(kernels : list) -> list:
    for kernel_spec in kernels:
        ...