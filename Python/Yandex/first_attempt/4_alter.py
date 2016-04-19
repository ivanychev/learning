import sys
#import bisect
import array

#def median(len_lst, sorted_lst):
#    if len_lst % 2 == 1:
#        return sorted_lst[len_lst // 2]
#    else:
#        return sorted_lst[len_lst // 2 - 1]

def median(sorted_args, arr, len_lst):
    arg = None
    if len_lst % 2 == 1:
        arg = sorted_args[len_lst // 2]
    else:
        arg = sorted_args[len_lst // 2 - 1]
    return arr[arg]

def argsort(seq, length):
    return sorted(range(length), key=seq.__getitem__)


def main(argv):
    inp = open("input.txt")
    num = int(inp.readline())
    arr = array.array('l', map(lambda x: int(x), inp.readline().split(" ")))
    args_sorted = array.array('i', argsort(arr, num))
    sum_medians = 0
    for idx in range(num - 1, -1, -1):
        sum_medians += median(args_sorted, arr, num)
        args_sorted.remove(idx)
        num -= 1
    sys.stdout.write(str(sum_medians))
    inp.close()


if __name__ == "__main__":
    sys.exit(main(sys.argv))
