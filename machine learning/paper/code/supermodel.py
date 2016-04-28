import numpy as np
import utils
import classifiers
import pandas as pd
from sklearn.metrics import roc_auc_score
from sklearn.base import BaseEstimator, ClassifierMixin
from sklearn.linear_model import LogisticRegression
from classifiers import spec_repr
from sklearn.cross_validation import StratifiedKFold
from sklearn.cross_validation import KFold
from sklearn.cross_validation import train_test_split
from robust_logregr import RobustLogregr


def to_csv(superm, X, y, margins=None, ending="", subfolder="csvs/"):
    name = superm.dataset_name + "_" + ending + ".csv"
    if margins is None:
        margins = superm.margins
    if superm.mask is None:
        col_names = ["y"] + ["X" + str(i) for i in range(1, X.shape[1] + 1)]
        + [spec_repr(val) for val in superm.specs]
    else:
        col_names = ["y"] + ["X" + str(i) for i in range(1, X.shape[1] + 1)]
        + list(np.array([spec_repr(val) for val in superm.specs])[superm.mask])
    print(y.shape)
    print(X.shape)
    print(margins.shape)
    df = pd.DataFrame(data=np.hstack((y.reshape((y.shape[0], 1)), X, margins)),
                      index=None,
                      columns=col_names)
    df["y"] = df["y"].astype("int")
    df.to_csv(subfolder + name, sep=",", header=True, index=False)
    return df


class SVNSupermodel(BaseEstimator, ClassifierMixin):
    def __init__(self,
                 specs=utils.get_classifier_specs(),
                 C=[10] * len(utils.get_classifier_specs()),
                 dataset_name="",
                 train_size=0.5,
                 algo="l2",
                 auc_window=None,
                 refit_after=False,
                 csv_export=False,
                 superclassifier="simple"):
        """
        specs                            kernel specifications (see utils.py)
        C           list (len(specs),)   regularization parameters for each
                                         kernel
        superclassifier                  model to aggregate margins
        dataset_name                     name of used dataset (used for verbose
                                         output)
        auc_window                       elitism, if not None, only classifiers
                                         in [best_auc, best_auc - auc_window]
                                         will be used by supermodel
        algo:
            l2                         naive l2-regularized regression
            l1                         l1-regularized logistic regression
            +                          choose positive
            l1+                        l1-reg + choose positive
        """
        assert len(specs) == len(C), "Specs and regularization constants arrays lengths don't match"
        assert 0 < train_size and train_size < 1, "Traing part must be in (0, 1)"
        assert algo in ["l1", "l1+", "+", "l2"], "Specified algorithm is invalid"
        assert auc_window is None or (0 < auc_window and auc_window < 1), "Auc_window must be in [0, 1] if specified"

        self.C = C
        self.specs = specs
        self.clfs = classifiers.get(self.specs, self.C)
        self.margins = None
        self.margin_mean_abs = None
        self.dataset_name = dataset_name
        self.mask = None
        self.algo = algo
        self.train_size = train_size
        self.auc_window = auc_window
        self.refit_after = refit_after
        self.csv_export = csv_export
        if algo in ["l1", "l1+"]:
            penalty = "l1"
        else:
            penalty = "l2"
        if superclassifier == "simple":
            self.superclassifier = LogisticRegression(penalty=penalty)
        elif superclassifier == "robust":
            self.superclassifier = RobustLogregr(penalty=penalty)

    def scale_train_margins(self, margins):
        abs_margins = np.abs(margins)
        self.margin_mean_abs = np.mean(abs_margins, axis=0)
        return margins / self.margin_mean_abs

    def scale_test_margins(self, margins):
        return self.mask_margin(margins / self.margin_mean_abs)

    def mask_margin(self, margin):
        if self.mask is None:
            return margin
        return margin[:, self.mask]

    def _get_train_validate(self, X, y):
        return train_test_split(X, y, train_size=self.train_size)

    def _fit_classifiers(self, X, y):
        for clf, spec in zip(self.clfs, self.specs):
            clf.fit(X, y)

    def _refit_classifiers(self, X, y):
        return self._fit_classifiers(X, y)

    def _condition_positive(self):
        return self.algo in ["l1+", "+"]

    def _condition_window(self):
        return self.auc_window is not None

    def _conditional_refit(self, X_val, y_val, verbose=False):
        if not self._condition_positive() and not self._condition_window():
            return
        if verbose:
            print("Logregr coefs before refit:\n",
                  self.superclassifier.coef_)
        if self._condition_positive():
            positive_coefs = self.superclassifier.coef_ > 0
            self.mask = positive_coefs.reshape(positive_coefs.shape[1])
        if self._condition_window():
            scores, _ = self.score_stats(X_val, y_val, verbose=False,
                                         predict_super=False)
            scores = np.array(scores)
            max_score = np.max(scores)
            threshold = max_score - self.auc_window
            if self.mask is not None:
                self.mask = self.mask & (scores >= threshold)
            else:
                self.mask = scores >= threshold
        if verbose:
            print(self.superclassifier.coef_.shape)
            print(positive_coefs.shape)
            print(self.margins.shape)
        self.margins = self.mask_margin(self.margins)
        self.superclassifier.fit(self.margins, y_val)

    def fit(self, X, y=None, verbose=True):
        """
        Fitting each SVM, calculating margins then fitting superclassifier
        """
        X_train, X_val, y_train, y_val = self._get_train_validate(
                                        X, y)
        self._fit_classifiers(X_train, y_train)
        self.margins = self.scale_train_margins(
                utils.get_margins(self.clfs, X_val)
                )
        self.superclassifier.fit(self.margins, y_val)
        if self.refit_after is True:
            self._refit_classifiers(X, y)
        self._conditional_refit(X_val, y_val)
        if self.csv_export:
            to_csv(self, X_val, y_val, ending="_validate")

        train_margins = utils.get_margins(self.clfs, X_train)
        train_margins = self.scale_test_margins(train_margins)
        if self.csv_export:
            to_csv(self, X_train, y_train, margins=train_margins, ending="_train")
        if verbose:
            print("Logregr coefs:\n", self.superclassifier.coef_)

    def predict(self, X, y=None):
        margins = utils.get_margins(self.clfs, X)
        margins = self.scale_test_margins(margins)
        return self.superclassifier.predict(margins)

    def predict_proba(self, X, y=None):
        margins = utils.get_margins(self.clfs, X)
        margins = self.scale_test_margins(margins)
        if self.csv_export:
            to_csv(self, X, y, margins=margins, ending="_test")
        return self.superclassifier.predict_proba(margins)

    def score(self, X, y=None):
        return roc_auc_score(y, self.predict_proba(X))

    def score_stats(self, X, y=None, verbose=True, predict_super=True):
        """
        Calculating ROC for each SVM and for supermodel
        """
        scores = []
        for clf, spec in zip(self.clfs, self.specs):
            prediction = clf.decision_function(X)
            scores.append(roc_auc_score(y, prediction))
            if verbose:
                print("%s ROC: %f" % (spec_repr(spec), scores[-1]))
        super_score = None
        if predict_super:
            super_score = roc_auc_score(y, self.predict_proba(X, y)[:, 1])
        if verbose:
            print("Superclassifier ROC: %f" % super_score)
        return scores, super_score

    def fit_score_stats(self, X_train, X_test, y_train, y_test, verbose=True):
        """
        Fitting and scoring combined
        """
        self.fit(X_train, y_train, verbose=verbose)
        if verbose:
            print("Fitted")
        return self.score_stats(X_test, y_test, verbose=verbose)

def mean_scores(scores):
    """
    returns mean score and its standard deviation for every model and for supermodel
    :param scores:  list of tuples,
    :return:
    """
    num = len(scores)
    classifiers_num = len(scores[0][0])
    # super_score = 0
    scores_matrix = np.zeros((classifiers_num + 1, num))
    # for that_class_scores, that_super_score in scores:
    #     class_scores += np.array(that_class_scores)
    #     super_score += that_super_score
    for idx, score in enumerate(scores):
        that_class_scores, that_super_score = score
        scores_matrix[0, idx] = that_super_score
        scores_matrix[1:, idx] = that_class_scores
    super_stats = (np.mean(scores_matrix[0]), np.std(scores_matrix[0]))
    classifiers_stats = (np.mean(scores_matrix[1:], axis=1), np.std(scores_matrix[1:], axis=1))
    return super_stats, classifiers_stats

def scores_stats(X, y,
                 cv_type="stratified",
                 n_folds=5, times=20,
                 only=None, verbose=True,
                 args={"algo": "l2", "auc_window": None, "refit_after": False}):
    """
    The function includes data splitting and scoring
    """
    scores = []
    for time in range(times):
        print(time, end=" ")
        if cv_type == "stratified":
            cv = StratifiedKFold(y, n_folds=n_folds, shuffle=True)
        elif cv_type == "simple":
            cv = KFold(np.size(y), n_folds=n_folds, shuffle=True)
        else:
            raise ValueError("Invalid cv_type")
        for idx, train_test in enumerate(cv):
            train, test = train_test
            superm = SVNSupermodel(**args)
            clfs_scores, super_score = \
                superm.fit_score_stats(X[train], X[test], y[train], y[test],
                                       verbose=verbose)
            scores.append((clfs_scores, super_score))
    print("Result samples = %d" % len(scores))
    return mean_scores(scores)

def test_supermodel(datasets, args, n_folds=5, times=20, verbose=False):
    for item in datasets:
        print(type(item))
        if isinstance(item, tuple):
            X, y = item[0], item[1]
        else:
            X, y, _ = utils.get_dataset(item)
            print("TESTING %s" % item.upper())
        print("Dataset shape: %s, %s" % (X.shape, y.shape))
        args["dataset_name"] = item
        super_res, classifiers_res = scores_stats(X, y, cv_type="stratified", n_folds=5, times=times, verbose=False, args=args)
        print("Classifiers results:")
        max_mean = 0
        max_std = 0
        for idx, val in enumerate(classifiers_res[0]):
            mean, std = (classifiers_res[0][idx], classifiers_res[1][idx])
            if mean > max_mean:
                max_mean = mean
                max_std = std
            print("Mean = %.4f, std = %.4f" % (mean, std))
        print("Max classifier mean:\nMean = %.4f, std = %.4f" % (max_mean, max_std))
        print("Superclassifier score")
        print("Mean = %.4f, std = %.4f" % (super_res[0], super_res[1]))