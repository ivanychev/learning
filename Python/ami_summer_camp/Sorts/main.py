import random
import heapsort_my.py
import mergesort_my.py
import qsort_my.py
import shellsort_my.py

"""def heapsort(s):
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

        s[0:len(s)-1] = heapsort(s[0:len(s)-1])
        return s
    else:
        return s
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
def qsort(s):

    tn = random.randint(0, len(s) -1)
    temp = s[tn]

    #print(temp,'\n',s)
    l = 0
    r = len(s) - 1

    a = 0
    b = len(s) -1
    #print(s)
    while l <= r :
        while s[l] < temp:
            l += 1
        while s[r] > temp:
            r -= 1
        if l<= r:
            s[l],s[r] = s[r], s[l]

            l+=1
            r-=1
    #print(temp,' ',s,'\n')
    if l < b:
        s[l:b+1] = qsort(s[l:b+1])
    if r > a:
        s[a:r+1] = qsort(s[a:r+1])
    #print(s,'\n')
    return s
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
"""
def main():
    i = input()
    i = int(i)
    x = 0
    s = []
    while x<i:
        s.append(random.randint(-99,99))
        x += 1

    s1, s2, s3, s4 = s, s, s, s

    print(s)
    print(heapsort_my.heapsort(s1))
    print(mergesort_my.mergesort(s2))
    print(qsort_my.qsort(s3))
    print(shellsort_my.shellsort(s4))

    if s1 == s2 == s3 == s4:
        print("TRUE")
    else:
        print("FALSE")

    return 0

main()

