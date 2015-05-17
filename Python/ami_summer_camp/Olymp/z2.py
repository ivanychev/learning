def shellsort(s):
    k = len(s) // 2

    while k > 0:
        x = 0
        while x <= len(s) - k - 1:
            j = x
            while (j >= 0) and (s[j]<s[j+k]):
                s[j+k], s[j] = s[j], s[j+k]
                j -= 1
            x += 1
        k = k // 2
    return s

def main():
    size = int(input())
    x = 0
    nums = []
    list_nums = []
    while x < size:
        inp = list(map(int, input().split()))
        list_nums += inp
        x += 1
    list_nums = shellsort(list_nums)

    out_nums = []
    for i in range (size ** 2):
        out_nums.append(0)
    wid = 0
    dip = 0
    count = 0
    x = 0
    while x < 2 * size - 1:
        wid = x
        while wid >= 0:
            dip = x - wid
            if (wid > (size - 1)) or (dip > (size - 1)):
                wid -= 1
                continue
            out_nums[wid + size * dip] = list_nums[count]
            count += 1
            wid -= 1
        x += 1
    y = 0
    count = 0
    for x in range(size):
        for y in range(size):
            print(out_nums[count], end = " ")
            count += 1
        print("\n", end = "")

    return 0

main()
