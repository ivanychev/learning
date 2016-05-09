import pandas as pd
import numpy as np
import features_generation

def prepare_dfs(dftrain, dftest):
    dftrain['Label'] = dftrain['Label'].map({'b': 0, 's': 1})
    return dftrain, dftest

def add_features(dftrain, dftest, features):
    dftrain_new = dftrain.copy()
    dftest_new = dftest.copy()
    for func in features_generation.new_features_funcs:
        print("Using %s func..." % func.__name__)
        new_test_features = func(dftest_new)
        new_train_features = func(dftrain_new)
        dftest_new = dftest_new.join(new_test_features)
        dftrain_new = dftrain_new.join(new_train_features)

    return dftrain_new, dftest_new

def rearrange_dataframes(dftrain, dftest):
    feature_cols = dftest.columns.tolist()
    target_col = ["Label"]
    weight_col = ["Weight"]
    train_cols = target_col + weight_col + feature_cols
    dftrain = dftrain[train_cols]
    return dftrain, dftest, feature_cols



def get_data(train_name, test_name):
    dftrain = pd.read_csv(train_name)
    dftest = pd.read_csv(test_name)

# rearranging columns in dataframes
    dftrain, dftest, features_cols = rearrange_dataframes(dftrain, dftest)
# add features
    dftrain, dftest = add_features(dftrain, dftest, features_cols)
    dftrain, dftest = prepare_dfs(dftrain, dftest)
    return dftrain, dftest