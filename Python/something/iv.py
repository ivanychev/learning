# Some cool Python things
#
# Sergey Ivanychev
#
import collections

def counted(n):
    if n % 100 == 11 or n % 100 == 12 or n % 100 == 13:
        return str(n) + "'th"
    last_digit = n % 10
    ending = {1:'st', 2:'nd', 3:'rd'}
    if last_digit in ending:
        return str(n) + "'" + ending[last_digit]
    return str(n) + "'th"


def del_by_index(lst, indexes):
    repeats = collections.Counter()
    l = len(lst)
    for key, val in repeats.iteritems():
        if not isinstance(key, int):
            raise ValueError("Indexes list element is not an integer")
        if val != 1:
            raise ValueError(counted(key) + ": Repeated indexes")
        if not ((0 <= key) and (key < l)):
            raise ValueError(counted(key) + ": Index out of range")

    for x in sorted(indexes, reverse=True):
        lst.pop(x)
    return lst
