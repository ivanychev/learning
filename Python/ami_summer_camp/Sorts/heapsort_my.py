from math import log2
import random

def heapsort(s):
    if len(s)>1:
        n = len(s) // 2 - 1
        while n>= 0:
            if (n == len(s) // 2 - 1):
                if (len(s)-1 >= 2*n+2):
                    if (s[2*n+2] > s[n]):
                        s[n], s[2*n+2] = s[2*n+2], s[n]
                if (len(s)-1 >= 2*n+1):
                    if (s[2*n+1] > s[n]):
                        s[n], s[2*n+1] = s[2*n+1], s[n]
            else:
                if (s[2*n+2] > s[n]):
                    s[n], s[2*n+2] = s[2*n+2], s[n]
                if (s[2*n+1] > s[n]):
                    s[n], s[2*n+1] = s[2*n+1], s[n]
            n -= 1
        s[len(s)-1], s[0] = s[0], s[len(s)- 1]
        print(s[len(s)-1])
        s[0:len(s)-1] = heapsort(s[0:len(s)-1])
        return s
    else:
        return s


"""def main():
    x = 0
    s = []
    while (x < 5):
        s.append(random.randint(1,50))
        x += 1
    print(s)
    heapsort(s)
    print(s,'\n')

    input()

    return 0


main()"""