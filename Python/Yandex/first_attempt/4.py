import sys
import bisect
import array

def median(len_lst, sorted_lst):
    if len_lst % 2 == 1:
        return sorted_lst[len_lst // 2]
    else:
        return sorted_lst[len_lst // 2 - 1]

def get_subset(last_num, last_idx, num, length):
    if last_num == None:
        return 0, length
    if num > last_num:
        return last_idx, length
    return 0, last_idx + 1

def main(argv):
    inp = open("input.txt")
    num = int(inp.readline())
    num_list = map(lambda x: int(x), inp.readline().split(" "))
    sum_medians = 0
    sorted_list = array.array('l', [])
    last_num = None
    last_idx = None
    for idx, num in enumerate(num_list):
        l, r = get_subset(last_num, last_idx, num, idx)
        insert_idx = bisect.bisect(sorted_list, num, l, r)
        sorted_list.insert(insert_idx, num)
        sum_medians += median(idx + 1, sorted_list)
        last_idx = insert_idx
        last_num = num
    sys.stdout.write(str(sum_medians))
    inp.close()

def main_old(argv):
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
