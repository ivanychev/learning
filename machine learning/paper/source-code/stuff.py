import utils
import sys
import classifiers
from matplotlib import pylab as pl
import numpy as np

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


CLF_DIFF_TYPES = {
    "sn": ("SV normalized symmetric difference", clf_symdiff_normalized),
    "s": ("SV symmetric difference", clf_symdiff)
}
def margin_cov_pic(margins, clfs, C, fig, diff_type = "sn"):
    diff = CLF_DIFF_TYPES[diff_type][1]
    clfs_num = len(clfs)
    covs_num = round(clfs_num * (clfs_num - 1) / 2)
    covs = np.zeros(covs_num)
    difs = np.zeros(covs_num)
    idx = 0
    for i in range(clfs_num):
        for j in range(i + 1, clfs_num):
            covs[idx] = np.corrcoef(margins[:, i], margins[:, j])[0, 1]
            difs[idx] = diff(clfs[i], clfs[j])
            idx += 1
    fig.scatter(difs, 1 - covs, marker='o', s=90, label="C = %f" % C, c=np.random.rand(3,1))

def spec_repr(spec):
    ret = "Kernel type: "
    if spec[0] == "linear":
        return ret + "linear"
    if spec[0] == "rbf":
        return ret + "rbf, gamma = %f" % spec[1]
    if spec[0] == "poly":
        return ret + "poly, degree = %d" % spec[1]
    if spec[0] == "ink":
        return ret + "ink, degree = %d, downer limit (a) = %f" % (spec[1], spec[2])

def print_kernel_info(C, clfs, specs, margins):
    print("C = %f" % C)
    for idx, clf in enumerate(clfs):
        print("%s\nSV number = %d" % (spec_repr(specs[idx]), clf.n_support_[0] + clf.n_support_[1]))
    print("")

def draw_corr_diff(dataset_name, C_list=[1.0], diff_type = "sn"):
    data = utils.get_data()
    dataset = data[dataset_name]
    print(dataset_name)
    print(dataset[0].shape)
    specs = utils.get_classifier_specs()
    fig = pl.figure(figsize=(8, 6), dpi=150)
    ax1 = fig.add_subplot(111)
    for C in C_list:
        clfs = classifiers.get(specs, C=C)
        utils.train_clfs(clfs, dataset[0], dataset[1])
        margins = utils.get_margins(clfs, dataset[0])
        print_kernel_info(C, clfs, specs, margins)
        margin_cov_pic(margins, clfs, C, ax1, diff_type=diff_type)
    pl.legend(loc='upper left')
    pl.xlabel(CLF_DIFF_TYPES[diff_type][0])
    pl.ylabel("Margin vectors correlation")
    pl.show()

def main(argv):
    draw_corr_diff("heart", [1])

if __name__ == "__main__":
    sys.exit(main(sys.argv))