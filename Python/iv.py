
""" @function   iv_fill_empty_str_values
    @brief      fills non-string values in string containing column
    @details    if there's no "Empty" word among the values, it will be used
                otherwise "Empty_1" or "Empty_2" (if there's Empty_1) and etc.

    @param      data_frame
                Pandas DataFrame
    @param      column_name string

    @return     transformed data_frame 
"""
def iv_fill_empty_str_values(data_frame, column_name):
    values = list(data_frame[column_name].unique())
    values = [x for x in values if type(x) == str]
    fill_template = 'Empty'
    fill = fill_template
    count = 0
    while fill in values:
        count += 1
        fill = fill_template + '_' + str(count) 

    def fill_data(row, column_name, values, fill):
        if not row[column_name] in values:
            return fill
        return row[column_name]
    
    data_frame[column_name] = data_frame.apply(lambda row: fill_data(row, column_name, values, fill), axis = 1)
    return data_frame



def iv_crossvalidate(str_classifier, folds, X, y)
    from sklearn import cross_validation
    from sklearn.metrics import accuracy_score
    
    average_score = 0
    skf = cross_validation.StratifiedKFold(train["Survived"], n_folds = folds)

    X = train[training_list]
    y = train["Survived"]
    for train_index, test_index in skf:
        bagging = BaggingClassifier(KNeighborsClassifier(), max_samples=0.5, max_features=0.5)
        y_train = y[train_index]
        y_test  = y[test_index]
        X_train = X.loc[train_index, :].fillna(-1)
        X_test  = X.loc[test_index, :].fillna(-1)
        bagging.fit(X_train, y_train)
        prediction = bagging.predict(X_test[X_test.columns])
        score = accuracy_score(y_test, prediction)
        average_score += score
    average_score /= folds
    print(average_score)
