import sys
import bisect

def median(len_lst, sorted_lst):
    if len_lst % 2 == 1:
        return sorted_lst[len_lst // 2]
    else:
        return sorted_lst[len_lst // 2 - 1]


def main(argv):
    inp = open("input.txt")
    num = int(inp.readline())
    num_list = map(lambda x: int(x), inp.readline().split(" "))
    sum_medians = 0
    sorted_list = []
    for idx, num in enumerate(num_list):
        bisect.insort(sorted_list, num)
        sum_medians += median(idx + 1, sorted_list)
    sys.stdout.write(str(sum_medians))
    inp.close()

if __name__ == "__main__":
    sys.exit(main(sys.argv))