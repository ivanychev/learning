import heart
import wine
import german
import spam
import housing
import numpy as np
import classifiers
from sklearn.cross_validation import KFold
from sklearn.cross_validation import StratifiedKFold
import sklearn
from sklearn.preprocessing import StandardScaler

DATA_MODULES = {
    "heart" : heart,
    "wine": wine,
    "german": german,
    "spambase": spam,
    "housing": housing,
}

def datasetsGenerator():
    for key, val in DATA_MODULES.items():
        yield key

datasets = datasetsGenerator()

def get_classifier_specs():
    """
    Procedure specifies interesting kernels that are observed in the project.
    If you want to change the set of classifiers, you are welcome to edit this function.
    Specs format available in docs and classifiers.py module
    :return: list of kernel specs, that are processed in get_classifiers()
    """
    specs = []
    specs.append(["linear"])
    specs.append(["poly", 2])
    specs.append(["poly", 3])
    specs.append(["poly", 4])
    specs.append(["ink", 1, -3])
    specs.append(["ink", 2, -3])
    for i in [0.0001, 0.001, 0.001, 0.01, 0.1, 1]:
        specs.append((["rbf", i]))
    return specs

def get_all_classifiers(C=0.1, spec_verbose=False):
    specs = get_classifier_specs()
    clfs = classifiers.get(specs, C=C)
    if spec_verbose == True:
        clfs = list(map(lambda x: (clfs[x], classifiers.spec_repr(specs[x])),
                    range(len(specs))))
    return clfs

def get_data(raw=False):
    """
    Loads data from processed sources
    :return: list of (X, y) tuples
    """
    data = []
    data.append(german.load(raw=raw))
    data.append(heart.load(raw=raw))
    data.append(wine.load(raw=raw))
    data.append(spam.load(raw=raw))
    data.append(housing.load(raw=raw))
    data_dict = {}
    for dataset in data:
        data_dict[dataset[2]] = (dataset[0], dataset[1])
    return data_dict

def get_dataset(name, raw=False):
    return DATA_MODULES[name].load(raw=raw)

def train_clfs(clfs, X_train, Y_train):
    for clf in clfs:
        clf.fit(X_train, Y_train)
    return None

def get_margins(clfs, X_train):
    margins = np.zeros((X_train.shape[0], len(clfs)))
    for idx, clf in enumerate(clfs):
        margins[:, idx] = clf.decision_function(X_train)
    return margins

def scale(X, train_idx, test_idx):
    scaler = StandardScaler()
    scaler.fit(X[train_idx])
    return scaler.transform(X[train_idx]), scaler.transform(X[test_idx])

SCORERS = {
    "accuracy": sklearn.metrics.accuracy_score,
    "roc": sklearn.metrics.roc_auc_score
}

def _get_data(dataset):
    if isinstance(dataset, str):
        load_data = DATA_MODULES[dataset].load
        X, y, _ = load_data(raw=True)
    elif isinstance(dataset, tuple):
        X, y = dataset[0], dataset[1]
    else:
        raise ValueError("Invalid dataset format")
    return X, y

def _get_cv(folds_type, folds, X, y, random_state=None):
    if folds_type == "simple":
        cv = KFold(X.shape[0], folds, random_state=random_state)
    elif folds_type == "stratified":
        cv = StratifiedKFold(y, folds, random_state=random_state)
    else:
        raise ValueError("Invalid folds type received")
    return cv

def test_classifier(dataset, clf, scoring_type="roc", folds=5, folds_type="stratified"):
    X, y = _get_data(dataset)
    cv = _get_cv(folds_type, 5, X, y)
    scores = []
    scorer = SCORERS[scoring_type]
    for train_idx, test_idx in cv:
        X_train, X_test = scale(X, train_idx, test_idx)
        clf.fit(X_train, y[train_idx])
        probs = clf.decision_function(X_test)
        score = scorer(y[test_idx], probs)
        scores.append(score)
    scores = np.array(scores)
    return np.mean(scores), np.std(scores), scores

def _get_dataset_name(dataset):
    if isinstance(dataset, str):
        return dataset
    dataset_name = None
    try:
        dataset_name = dataset[2]
    except IndexError as a:
        raise ValueError("Invalid dataset format")
    return dataset_name


def test_classifiers(dataset, scoring_type="accuracy", folds=5, folds_type="stratified"):
    dataset_name = _get_dataset_name(dataset)
    print("Testing %s dataset...\nFolds = %d, Folds type = %s" % (dataset_name, folds, folds_type))
    clfs = get_all_classifiers(spec_verbose=True)
    for clf in clfs:
        score, std_score, scores = test_classifier(dataset, clf[0])
        print(clf[1])
        print("Score = %f, std = %f" % (score, std_score))
    print("Testing %s dataset finished\n" % dataset_name)
