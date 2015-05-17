def shellsort(s):
    k = len(s) // 2

    while k > 0:
        x = 0
        while x <= len(s) - k - 1:
            j = x
            while (j >= 0) and (s[j]>s[j+k]):
                s[j+k], s[j] = s[j], s[j+k]
                j -= 1
            x += 1
        k = k // 2
    return s

def main():
    nums = list(map(float, input().split()))
    sign = []
    plus = []
    minus = []
    for x in nums:
        if x > 0:
            plus.append(x)
            sign.append(1)
        else:
            minus.append(x)
            sign.append(-1)
    plus = shellsort(plus)

    c_plus = 0
    c_minus = 0

    for x in sign:
        if x == 1:
            print(plus[c_plus], end = " ")
            c_plus += 1
        else:
            print(minus[c_minus], end = " ")
            c_minus += 1
    return 0

main()