"""
This module loads a set of models used in classification. Supported kernels are
 - Linear
 - RBF
 - INK-spline
 - Polynomial

 Author:    Sergey Ivanychev
 Revision:  3
"""

RANDOM_STATE = 42
MAX_ITER = 1000000

import ink
from sklearn.svm import SVC
import numbers

KERINVAL = "Invalid specification of kernel"

def spec_repr(spec):
    ret = "Kernel type: "
    if spec[0] == "linear":
        return ret + "linear"
    if spec[0] == "rbf":
        return ret + "rbf, gamma = %f" % spec[1]
    if spec[0] == "poly":
        return ret + "poly, degree = %d" % spec[1]
    if spec[0] == "ink":
        return ret + "ink, degree = %d, downer limit (a) = %f" % (spec[1], spec[2])

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
    assert len(spec) == 3 and _is_number(spec[1]) and _is_number(spec[2]), KERINVAL
    return {"kernel":ink.get_sklearn_ink(degree=spec[1], a = spec[2])}

KERNELS = {
    "linear":_linear_args,
    "rbf":_rbf_args,
    "ink":_ink_args,
    "poly":_poly_args
}

def _get_kernel(spec):
    return KERNELS[spec[0]](spec)


def get(kernel_specs : list, C = 0.1) -> list:
    """

    :param kernels: list of lists or tuples with format
                    [[kernel_name, *optional_kernel_args], [...], ...]
                    Kernel names(n_args):
                        "linear"(0):   no additional args
                        "rbf"(1):      gamma (float)
                        "ink"(2):      degree, a
                        "poly"(1):     degree
    :param C:       regularization factor (int or list)
    :return:        List of initialized classifiers
    """
    cls_list = []
    if _is_number(C):
        C = [C] * len(kernel_specs)
    for idx, kernel_spec in enumerate(kernel_specs):
        cls = SVC(C=C[idx], random_state=RANDOM_STATE,max_iter=MAX_ITER, **_get_kernel(kernel_spec))
        cls_list.append(cls)
    return cls_list