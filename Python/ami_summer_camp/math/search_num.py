__author__ = 'Sergey Ivanychev'

import string
import math

def main():
    num = list(map(float, input().split()))
    expnum = float(input())

    x = 0

    x1 = 0
    x2 = len(num) - 1

    x = math.floor((x2 - x1)/ 2)

    """if (num == []):
        print("empty list")
        return 0
    if (expnum > num[x2]) or (expnum < num[x1]):
        print ("no such number")
        return 0
    """
    x_last =  - 5
    i = 2
    step = 0
    while (num[x] != expnum):
        step = math.floor((x2 - x1) / (2 ** i))
        if step < 1:
            step = 1
        if expnum > num[x]:
            x += step
            if (x > x2) or (x < 0) or (x == x_last):
                print("no such number")
                return 0
            continue
        if expnum < num[x]:
            x -= step
            if (x > x2) or (x < 0) or (x == x_last):
                print("no such number")
                return 0
            continue
        i += 1
    print(x+1)

    return 0

main()