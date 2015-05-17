__author__ = 'Sergey Ivanychev'

def vector(x1, y1, x2, y2):
        return x1*y2 - x2*y1

def segments(x11,y11,x12,y12,x21,y21,x22,y22):
    def vector(x1, y1, x2, y2):
        return x1*y2 - x2*y1

    x1 = x12 - x11
    y1 = y12 - y11
    x2 = x22 - x21
    y2 = y22 - y21

    flag = 0

    vec11 = vector(x1,y1,x21 - x12, y21 - y12)
    vec12 = vector(x1,y1,x22 - x12, y22 - y12)
    if (vec11 > 0 and vec12 < 0) or (vec11 < 0 and vec12 > 0):
        flag += 1

    if (vec11 == 0) and (vec12 == 0):
        if (x21 > x11) and (x21 < x12) or (x21 < x11) and (x21 > x12) or (x22 > x11) and (x22 < x12) or (x22 < x11) and (x22 > x12):
            flag += 2

    vec11 = vector(x2, y2, x12 - x22, y12 - y22)
    vec12 = vector(x2, y2, x11 - x22, y11 - y22)
    if (vec11 > 0 and vec12 < 0) or (vec11 < 0 and vec12 > 0):
        flag += 1

    if flag >= 2:
        return 1
    else:
        return 0


def main():
    mn1 = list(map(float, input().split()))
    mn2 = list(map(float, input().split()))
    flag = 0
    for x in range(len(mn1)//2):
        x11 = mn1[2*x]
        y11 = mn1[2*x + 1]

        if x == len(mn1)//2 - 1:
            x12 = mn1[0]
            y12 = mn1[1]
        else:
            x12 = mn1[2*x + 2]
            y12 = mn1[2*x + 3]
        for y in range(len(mn2)//2):
            x21 = mn2[2*y]
            y21 = mn2[2*y + 1]

            if y == len(mn2)//2 - 1:
                x22 = mn2[0]
                y22 = mn2[1]
            else:
                x22 = mn2[2*y + 2]
                y22 = mn2[2*y + 2]
            flag += segments(x11,y11,x12,y12,x21,y21,x22,y22)
    if flag >0:
        print("YES")
    else:
        if len(mn2) == 2 and len(mn1) == 2:
            print("NO")
            return 0
        if len(mn1) < len(mn2):
            copy = mn1[:]
            mn1 = mn2[:]
            mn2 = copy


        mn = set()
        y2 = mn2[1]
        x2 = mn2[0]

        for x in range(len(mn1)//2):
            x11 = mn1[2*x]
            y11 = mn1[2*x + 1]

            if x == len(mn1)//2 - 1:
                x12 = mn1[0]
                y12 = mn1[1]
            else:
                x12 = mn1[2*x + 2]
                y12 = mn1[2*x + 3]

            x1 = x12 - x11
            y1 = y12 - y11

            sign = vector(x1,y1,x2 - x12,y2 - y12)
            if sign > 0:
                mn.add(1)
            if sign < 0:
                mn.add(-1)
        if (-1 in mn and 1 not in mn) or (1 in mn and -1 not in mn):
            print("YES")
        else:
            print("NO")

    return 0

main()