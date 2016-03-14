def clf_symdiff(clf1, clf2):
    sv_set1 = set(clf1.support_)
    sv_set2 = set(clf2.support_)
    return len(sv_set1 ^ sv_set2)

def clf_symdiff_normalized(clf1, clf2):
    sv_set1 = set(clf1.support_)
    sv_set2 = set(clf2.support_)
    return len(sv_set1 ^ sv_set2) / len(sv_set1 | sv_set2)

def clf_new(clf1, clf2):
    sv_set1 = set(clf1.support_)
    sv_set2 = set(clf2.support_)