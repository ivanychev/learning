from sklearn.base import BaseEstimator, ClassifierMixin
import utils
import classifiers
import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_auc_score
from classifiers import spec_repr
from sklearn.cross_validation import StratifiedKFold
from sklearn.cross_validation import KFold

class SVNSupermodel(BaseEstimator, ClassifierMixin):
    def __init__(self,
                 specs=[['linear'], ['poly', 2], ['poly', 3], ['poly', 4],
                        ['rbf', 0.0001], ['rbf', 0.001], ['rbf', 0.01], ['rbf', 0.1], ['rbf', 1],
                        ["ink", 1, -3], ["ink", 2, -3]],
                 C = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], superclassifier = LogisticRegression()):
        assert len(specs) == len(C), "Specs and regularization constants arrays lengths don't match"
        self.C = C
        self.specs = specs
        self.clfs = classifiers.get(self.specs, self.C)
        self.margins = None
        self.superclassifier = superclassifier
    def fit(self, X, y=None, verbose=True):
        for clf, spec in zip(self.clfs, self.specs):
            clf.fit(X, y)
            if verbose:
                print("Fitted %s" % spec_repr(spec))
        self.margins = utils.get_margins(self.clfs, X)
        if verbose:
            print("Margins calculated")
        self.superclassifier.fit(self.margins, y)
    def predict(self, X, y=None):
        margins = utils.get_margins(self.clfs, X)
        return self.superclassifier.predict(margins)
    def predict_proba(self, X, y=None):
        margins = utils.get_margins(self.clfs, X)
        return self.superclassifier.predict_proba(margins)
    def score(self, X, y=None):
        return roc_auc_score(y, self.predict_proba(X))
    def score_stats(self, X, y=None, verbose=True):
        scores = []
        for clf, spec in zip(self.clfs, self.specs):
            prediction = clf.decision_function(X)
            scores.append(roc_auc_score(y, prediction))
            if verbose:
                print("%s ROC: %f" % (spec_repr(spec), scores[-1]))
        super_score = roc_auc_score(y, self.predict_proba(X)[:, 0])
        if verbose:
            print("Superclassifier ROC: %f" % super_score)
        return scores, super_score
    def fit_score_stats(self, X_train, X_test, y_train, y_test, verbose=True):
        self.fit(X_train, y_train, verbose=verbose)
        if verbose:
            print("Fitted")
        return self.score_stats(X_train, y_train, verbose=verbose)
    def cross_val_stats(self, X, y, cv_type="stratified", n_folds=5):
        if cv_type == "stratified":
            cv = StratifiedKFold(y, n_folds=n_folds)
        elif cv_type == "simple":
            cv = KFold(np.size(y), n_folds=n_folds)
        else:
            raise ValueError("Invalid cv_type")
        scores = []
        for train, test in cv:
            clfs_scores, super_score = \
                self.fit_score_stats(X[train], X[test], y[train], y[test], verbose=True)
            scores.append((clfs_scores, super_score))
        return scores