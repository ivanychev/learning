import random


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
"""def main():
    s = []

    x = 0

    while (x<10):
        s.append(random.randint(0,50))
        x += 1
    print(s)
    s = shellsort(s)

    print(s)

main()"""
