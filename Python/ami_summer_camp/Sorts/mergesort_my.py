import random

def mergesort(s):
    if len(s) == 1:
        return s
    elif len(s) == 2:
        if s[0] > s[1]:
            s[0], s[1] = s[1], s[0]
        return s
    else:
        k = (len(s) // 2) - 1
        s1 = mergesort(s[0:k+1])
        s2 = mergesort(s[k+1:len(s)])

        i , j = 0, 0
        c = 0

        while (i < k+1) and (j < len(s) - k - 1):
            if s1[i] < s2[j]:
                s[i+j] = s1[i]
                i += 1
            else:
                s[i+j] = s2[j]
                j += 1

        if (i == k + 1):
            for c in s2[j:len(s)-k-1]:
                s[i+j] = c
                j += 1
        if (j == len(s) - k - 1):
            for c in s1[i:k+1]:
                s[i+j] = c
                i += 1
        return s

"""def main():
    x = 0
    #s = [5, 4, 3, 2, 1, 0]
    s = []
    while (x < 10):
        s.append(random.randint(1,50))
        x += 1

    print(s)
    print(mergesort(s))
    input()

    return 0


main()"""