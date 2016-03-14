import heart
import wine
import german
import numpy as np

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
    # specs.append(["ink", 1, -3])
    # specs.append(["ink", 2, -3])
    for i in [0.0001, 0.001, 0.01, 0.1, 1]:
        specs.append((["rbf", i]))
    return specs

def get_data():
    """
    Loads data from processed sources
    :return: list of (X, y) tuples
    """
    data = []
    data.append(german.load())
    data.append(heart.load())
    data.append(wine.load())

    data_dict = {}
    for dataset in data:
        data_dict[dataset[2]] = (dataset[0], dataset[1])
    return data_dict

def train_clfs(clfs, X_train, Y_train):
    for clf in clfs:
        clf.fit(X_train, Y_train)
    return None

def get_margins(clfs, X_train):
    margins = np.zeros((X_train.shape[0], len(clfs)))
    for idx, clf in enumerate(clfs):
        margins[:, idx] = clf.decision_function(X_train)
    return margins
