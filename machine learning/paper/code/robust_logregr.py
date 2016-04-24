"""
Logistic regression with positive output weights constraints.

Revision:   1
Author:     Sergey Ivanychev
"""


import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin
from scipy.optimize import minimize
from numpy.linalg import norm

def _sigmoid(x):
    return 1 / (1 + np.exp(-x))

class RobustLogregr(BaseEstimator, ClassifierMixin):
    def __init__(self,
                 penalty="l2",
                 C=1.0,
                 verbose=True):
        self.penalty = penalty
        self.C = C
        self.verbose = verbose
        self.coef_ = None

    def _log(self, *args, **kwargs):
        if self.verbose is False:
            return
        print(*args, **kwargs)

    def _get_cost_function(self, X, y):
        if self.penalty == "l1":
            def reg(w):
                return norm(w, 1)
        elif self.penalty == "l2":
            def reg(w):
                return (1/2)*norm(w, 2)**2
        def Q(wc):
            size = wc.size
            w = wc[:-1]
            c = wc[-1]
            costs = np.log(np.exp(-np.dot(X, w)*y + c) + 1)
            return reg(w) + self.C*np.sum(costs)
        return Q

    def fit(self, X, y=None, w_start = None):
        y[y == 0] = -1

        Q = self._get_cost_function(X, y)
        if w_start == None:
            w_start = np.zeros(X.shape[1] + 1)
        bounds = [(0, None)] * w_start.size
        opt_res = minimize(fun=Q, x0=w_start, bounds=bounds)
        if opt_res.success is False:
            self._log("Optimizer failed to execute\n%s", str(opt_res))
        self.coef_ = opt_res.x[:-1]
        self.intercept_ = opt_res.x[-1]

    def predict(self, X):
        return np.sign(np.dot(X, self.coef_) + self.intercept_)

    def predict_proba(self, X):
        prob1 = _sigmoid((np.dot(X, self.coef_) + self.intercept_) * 1)
        prob0 = 1 - prob1
        return np.transpose(np.vstack((prob0, prob1)))