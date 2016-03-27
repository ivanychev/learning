from sklearn.base import BaseEstimator, ClassifierMixin
import utils
import classifiers
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

class SVNSupermodel(BaseEstimator, ClassifierMixin):
    def __init__(self,
                 specs=[['linear'], ['poly', 2], ['poly', 3], ['poly', 4],
                        ['rbf', 0.0001], ['rbf', 0.001], ['rbf', 0.01], ['rbf', 0.1], ['rbf', 1]],
                 C = [1, 1, 1, 1, 1, 1, 1, 1, 1], superclassifier = LogisticRegression()):
        assert len(specs) == len(C), "Specs and regularization constants arrays lengths don't match"
        self.C = C
        self.specs = specs
        self.clfs = classifiers.get(self.specs, self.C)
        self.margins = None
        self.superclassifier = superclassifier
    def fit(self, X, y=None):
        for clf in self.clfs:
            clf.fit(X, y)
        self.margins = utils.get_margins(self.clfs, X)
        self.superclassifier.fit(self.margins, y)
    def predict(self, X, y=None):
        margins = utils.get_margins(self.clfs, X)
        return self.superclassifier.predict(margins)
    def predict_proba(self, X, y=None):
        margins = utils.get_margins(self.clfs, X)
        return self.superclassifier.predict_proba(margins)
    def score(self, X, y=None):
        return accuracy_score(self.predict(X), y)