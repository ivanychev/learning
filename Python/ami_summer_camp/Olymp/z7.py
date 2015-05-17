__author__ = 'Sergey Ivanychev'

def digsum(x):
    s = x
    while s > 9:
        dubs = s
        s = 0
        while dubs > 0:
            s += dubs % 10
            dubs //= 10
    return s

def main():
    inp = list(map(int, input().split()))
    num = inp[0]
    ten = 10
    l = 1
    while num > ten:
        ten *= 10
        l += 1
    for i in range(l-1):
        s1 = num % (10 **(i + 1))
        s2 = num // (10 **(i + 1))
        if digsum(s1) == digsum(s2):
            print("YES")
            return 0
    print("NO")
    return 0

main()