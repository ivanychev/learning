"""
This module loads a set of models used in classification. Supported kernels are
 - Linear
 - RBF
 - INK-spline
 - Polynomial

 Author:    Sergey Ivanychev
 Revision:  1
"""

RANDOM_STATE = 42

import ink
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
    assert len(spec) == 3 and _is_number(spec[1]) and _is_number(spec[2]), KERINVAL
    return {"kernel":ink.ink_svc_get(degree=spec[1], a = spec[2])}

KERNELS = {
    "linear":_linear_args,
    "rbf":_rbf_args,
    "ink":_ink_args,
    "poly":_poly_args
}

def _get_kernel(spec):
    return KERNELS[spec[0]](spec)


def get(kernel_specs : list, C: int = 0.1) -> list:
    """

    :param kernels: list of lists or tupels with format
                    [[kernel_name, *optional_kernel_args], [...], ...]
                    Kernel names(n_args):
                        "linear"(0):   no additional args
                        "rbf"(1):      gamma (float)
                        "ink"(2):      degree, a
                        "poly"(1):     degree
    :param C:       regularization factor
    :return:        List of initialized classifiers
    """
    cls_list = []
    for kernel_spec in kernel_specs:
        cls = SVC(C=C, random_state=RANDOM_STATE, **_get_kernel(kernel_spec))
        cls_list.append(cls)
    return cls_list