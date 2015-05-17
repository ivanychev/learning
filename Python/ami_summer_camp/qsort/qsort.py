import random


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
        while s[l] > temp:
            l += 1
        while s[r] < temp:
            r -= 1
        if l<= r:
            s[l],s[r] = s[r], s[l]

            l += 1
            r -= 1
    #print(temp,' ',s,'\n')
    if l < b:
        s[l:b+1] = qsort(s[l:b+1])
    if r > a:
        s[a:r+1] = qsort(s[a:r+1])
    #print(s,'\n')
    return s

"""def main():
    x = 0
    s = []
    while (x < 10):
        s.append(random.randint(1,50))
        x += 1

    print(s,'\n')
    qsort(s)


    print(s)
    input()

    return 0


main()"""